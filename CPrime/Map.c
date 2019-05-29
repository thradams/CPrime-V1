
#include "Map.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Mem.h"

/**
* Simple Bob Jenkins's hash algorithm taken from the
* wikipedia description.
*/
static uint32_t HashFunc(const char* a)
{
    //assert(a != NULL);
    int len = strlen(a);
    const char* key = a;
    uint32_t hash = 0;
   

    for (int i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

bool Bucket_Reserve(Bucket* p, int nelements);

bool BucketItem_InitMoveKey(struct BucketItem* node,
                              int hash,
                              String** key /*in out*/,
                              void* data)
{
    node->data = data;
    node->hash = hash;

    node->key = *key;
    *key = NULL;

    return true;
}


bool BucketItem_Init(struct BucketItem* node,
                       int hash,
                       const char* key,
                       void* data)
{
    node->key = StrDup(key);    
    node->data = data;
    node->hash = hash;
    return true;
}

bool BucketItem_CreateMoveKey(struct BucketItem** pp,
                                int hash,
                                String** key,
                                void* data)
{
    bool result = false /*nomem*/;
    struct BucketItem* node = (struct BucketItem*)Malloc(sizeof(struct BucketItem) * 1);
    if (node)
    {
        BucketItem_InitMoveKey(node,
                               hash,
                               key,
                               data);
        *pp = node;
        result = true;
    }
    return result;
}

bool BucketItem_Change(struct BucketItem* p,
                         void* data)
{
    p->data = data;
    return true;
}

void BucketItem_Destroy(struct BucketItem* node, void(*pfDestroyData)(void*))
{
    Free(node->key);
    if (pfDestroyData)
    {
        pfDestroyData(node->data);
    }
}

void BucketItem_Delete(struct BucketItem* p, void(*pfDestroyData)(void*))
{
    if (p)
    {
        BucketItem_Destroy(p, pfDestroyData);
        Free(p);
    }
}

bool Bucket_Init(Bucket* p, int capacity)
{
    bool result = true;
    p->data = NULL;
    p->size = 0;
    p->capacity = 0;

    if (capacity > 0)
    {
        result = Bucket_Reserve(p, capacity);
    }

    return result;
}

bool Bucket_Create(Bucket** pp)
{
    bool result = false /*nomem*/;
    Bucket*  p = (Bucket*)Malloc(sizeof(Bucket) * 1);
    if (p)
    {
        result = Bucket_Init(p, 0);
        if (result == true)
        {
            *pp = p;
            p = NULL;
        }
        Free(p);
    }
    return result;
}


void Bucket_Destroy(Bucket* p, void(*pfDestroyData)(void*))
{
    for (int i = 0; i < p->size; i++)
    {
        BucketItem_Delete(p->data[i], pfDestroyData);
    }
    Free(p->data);
}


void Bucket_Delete(Bucket* p, void(*pfDestroyData)(void*))
{
    if (p)
    {
        Bucket_Destroy(p, pfDestroyData);
        Free(p);
    }
}


bool Bucket_Reserve(Bucket* p, int nelements)
{
    bool r = true;

    if (nelements > p->capacity)
    {
        struct BucketItem** pnew = (struct BucketItem**)Realloc(p->data,
                            (nelements + 1) * sizeof(p->data[0]));

        if (pnew)
        {
            if (p->data == NULL)
            {
                pnew[0] = NULL;
            }

            p->data = pnew;
            p->capacity = nelements;
        }
        else
        {
            //assert(false);
            r = false /*nomem*/;
        }
    }

    return r;
}
static bool Grow(Bucket* p, int nelements)
{
    bool r = true;

    if (nelements > p->capacity)
    {
        int new_nelements = p->capacity + p->capacity / 2;

        if (new_nelements < nelements)
        {
            new_nelements = nelements;
        }

        r = Bucket_Reserve(p, new_nelements);
    }

    return r;
}

bool Bucket_Append(Bucket* p, struct BucketItem* pItem)
{
    bool result = Grow(p, p->size + 1);

    if (result == true)
    {
        p->data[p->size] = pItem;
        p->size++;
    }

    return result;
}

static int FindNodeIndex(Bucket* bucket, uint32_t hash, const char* key)
{
    //assert(key != NULL);
    for (int i = 0; i < bucket->size; i++)
    {
        struct BucketItem* node = bucket->data[i];
        if (node->hash == hash &&
                strcmp(node->key, key) == 0)
        {
            return (int)i;
        }
    }

    return -1;
}

bool RemoveBucketItem(Bucket* bucket,
                        uint32_t hash,
                        const char* key,
                        void** ppData)
{
    //assert(key != NULL);
    *ppData = NULL; //out

    int index = FindNodeIndex(bucket, hash, key);
    bool result = index != -1 ? true : false;

    if (result == true)
    {
        //ponteiro de item que vai ser removido (out)
        *ppData = bucket->data[index]->data;

        if (index != (int)(bucket->size) - 1)
        {
            //swap  dos ponteiros de [index] e [size - 1]
            struct BucketItem* pTemp = bucket->data[bucket->size - 1];
            bucket->data[bucket->size - 1] = bucket->data[index];
            bucket->data[index] = pTemp;
        }

        BucketItem_Delete(bucket->data[bucket->size - 1], NULL);
        bucket->size--;
    }


    return result;
}


bool Buckets_Init(Buckets* p,
                    int size)
{
    bool result = false /*nomem*/;
    p->data = NULL;
    p->size = size;

    p->data = (Bucket**)Malloc(sizeof(Bucket*) * size);
    if (p->data)
    {
        for (int i = 0; i < size; i++)
        {
            p->data[i] = NULL;
        }
        result = true;
    }

    return result;
}

void Buckets_Destroy(Buckets* p, void(*pfDestroyData)(void*))
{
    for (int i = 0; i < p->size; i++)
    {
        Bucket_Delete(p->data[i],
                      pfDestroyData);
    }
    Free(p->data);
}


bool Map_Init(Map* map, int nBuckets)
{
    map->Size = 0;
    bool result = Buckets_Init(&map->buckets, nBuckets);
    if (result == true)
    {
    }
    return result;
}

bool Map_Create(Map** pp, int nBuckets)
{
    bool result = false /*nomem*/;
    Map* p = (Map*)Malloc(sizeof(Map));
    if (p)
    {
        result = Map_Init(p, nBuckets);
        if (result == true)
        {
            *pp = p;
        }
        else
        {
            Free(p);
        }
    }
    return result;
}

void Map_Destroy(Map* map, void(*pfDestroyData)(void*))
{
    Buckets_Destroy(&map->buckets, pfDestroyData);
}

void Map_Delete(Map* p, void(*pfDestroyData)(void*))
{
    Map_Destroy(p, pfDestroyData);
    Free((void*)p);
}

struct BucketItem* Map_FindNode(Map* map, const char* key)
{
    if (map->buckets.data == NULL)
    {
        return NULL;
    }

    //assert(key != NULL);
    uint32_t hash = HashFunc(key);
    int bucket_n = hash % map->buckets.size;

    Bucket* pBucket = map->buckets.data[bucket_n];

    if (pBucket == NULL)
    {
        return NULL;
    }

    int i = FindNodeIndex(pBucket, hash, key);
    if (i == -1)
    {
        return NULL;
    }

    return pBucket->data[i];
}


bool Map_SetMoveKey(Map* map, String** key, void* data)
{
    //assert(key != NULL);
    bool result;

    struct BucketItem* pNode = Map_FindNode(map, *key);
    if (pNode)
    {
        return BucketItem_Change(pNode, data);
    }

    if (map->buckets.size == 0)
    {
        Buckets_Init(&map->buckets, 100);
    }

    uint32_t hash = HashFunc(*key);
    int bucket_n = hash % map->buckets.size;
    Bucket* bucket = map->buckets.data[bucket_n];

    if (bucket == NULL)
    {
        result = Bucket_Create(&bucket);
        if (result == true)
        {
            map->buckets.data[bucket_n] = bucket;
        }
    }
    else
    {
        result = true;
    }

    if (result == true)
    {
        struct BucketItem* node;
        result = BucketItem_CreateMoveKey(&node,
                                          hash,
                                          key,
                                          data);
        if (result == true)
        {
            result = Bucket_Append(bucket, node /*moved*/);
        }
    }

    if (result == true)
    {
      map->Size++;
    }

    return result;
}

bool Map_Set(Map* map, const char* key, void* data)
{
    //assert(key != NULL);
    void* pv;
    bool result = Map_Find(map, key, &pv);
    if (result == true)
    {
        return false;
        ////assert(false);
    }


    //assert(key != NULL);
    String* /*@auto*/ localkey = StrDup(key);
    result = Map_SetMoveKey(map, &localkey, data);
    Free(localkey);
    return result;
}


bool Map_Find(Map* map, const char* key, void** pp)
{
    //assert(key != NULL);
    struct BucketItem* pNode = Map_FindNode(map, key);
    bool result = pNode ? true : false;

    if (result == true)
    {
        *pp = pNode->data;
    }

    return result;
}

void* Map_Find2(Map* map, const char* key)
{
    void* pv;
    bool result = Map_Find(map, key, &pv);

    return result == true ? pv : NULL;
}

bool Map_DeleteEx(Map* map, const char* key, void** pp)
{
    //assert(key != NULL);
    uint32_t hash = HashFunc(key);
    int bucket_n = hash % map->buckets.size;

    Bucket* bucket = map->buckets.data[bucket_n];

    if (bucket == NULL)
    {
        return false;
    }

    bool result = RemoveBucketItem(bucket, hash, key, pp);

    if (result == true)
    {
      map->Size--;
    }
    return result;
}

bool Map_DeleteItemOpt(Map* map, const char* key, void(*pfDestroyData)(void*))
{
    //assert(key != NULL);
    void* p;
    bool result = Map_DeleteEx(map, key, &p);
    if (result == true)
    {
        if (pfDestroyData != NULL)
        {
            pfDestroyData(p);
        }
    }
    return result;
}

bool Map_DeleteItem(Map* map, const char* key, void(*pfDestroyData)(void*))
{
    bool result = Map_DeleteItemOpt(map, key, pfDestroyData);
    void* p;
    ////assert(Map_Find(map, key, &p) != true);
    if (Map_Find(map, key, &p) == true)
    {
        //assert(false);
        Map_DeleteItemOpt(map, key, pfDestroyData);
    }
    return result;
}


void Map_Print(Map* map)
{
    for (int i = 0; i < map->buckets.size; i++)
    {
        Bucket* data = map->buckets.data[i];
        if (data != NULL)
        {
            for (int k = 0; k < data->size; k++)
            {
                struct BucketItem* node = data->data[k];
                printf("%s", node->key);
            }
        }
    }
}


void Buckets_Swap(Buckets* b1, Buckets* b2)
{
    Bucket** data2 = b2->data;
    int size2 = b2->size;

    b2->data = b1->data;
    b2->size = b1->size;

    b1->data = data2;
    b1->size = size2;

}

void Map_Swap(Map* map, Map* map2)
{
  Map temp = *map2;
  *map2 = *map;
  *map = temp;
  //Buckets_Swap(&map->buckets, &map2->buckets);
}


////

bool MultiMap_Init(MultiMap* map, int nBuckets)
{
  map->Size = 0;
  bool result = Buckets_Init(&map->buckets, nBuckets);
  if (result == true)
  {
  }
  return result;
}

void MultiMap_Destroy(MultiMap* map, void(*pfDestroyData)(void*))
{
  Buckets_Destroy(&map->buckets, pfDestroyData);
}

bool MultiMap_Add(MultiMap* map, const char* key, void* data)
{
  //assert(key != NULL);
  bool result;
  
  uint32_t hash = HashFunc(key);
  int bucket_n = hash % map->buckets.size;
  Bucket* bucket = map->buckets.data[bucket_n];

  if (bucket == NULL)
  {
    //Não existia..criar
    result = Bucket_Create(&bucket);
    if (result == true)
    {
      map->buckets.data[bucket_n] = bucket;
    }
  }
  else
  {
    result = true;
  }

  if (result == true)
  {
    //Adiciona no fim - não verifica se ja existe
    String * /*@auto*/stemp = StrDup(key);
    
    struct BucketItem* node;
    result = BucketItem_CreateMoveKey(&node,
      hash,
      &stemp,
      data);

    Free(stemp);

    if (result == true)
    {
      result = Bucket_Append(bucket, node /*moved*/);
    }
  }

  if (result == true)
  {
    map->Size++;
  }

  return result;
}


Bucket*  MultiMap_FindBucket(MultiMap* map, const char* key)
{
  if (map->buckets.data == NULL)
  {
    return NULL;
  }

  //assert(key != NULL);
  uint32_t hash = HashFunc(key);
  int bucket_n = hash % map->buckets.size;

  Bucket*  pBucket = map->buckets.data[bucket_n];

  if (pBucket == NULL)
  {
    return NULL;
  }
  
  return pBucket;
}

void MultiMap_Swap(MultiMap* map, MultiMap* map2)
{
  MultiMap temp = *map2;
  *map2 = *map;
  *map = temp;  
}