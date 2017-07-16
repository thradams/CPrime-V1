
#include "Map.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/**
* Simple Bob Jenkins's hash algorithm taken from the
* wikipedia description.
*/
static uint32_t HashFunc(const char* a)
{
    ASSERT(a != NULL);
    size_t len = strlen(a);
    const char* key = a;
    uint32_t hash = 0;
   

    for (uint32_t i = 0; i < len; ++i)
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

Result Bucket_Reserve(Bucket* p, size_t nelements);

Result BucketItem_InitMoveKey(BucketItem* node,
                              int hash,
                              String* key /*in out*/,
                              void* data)
{
    node->data = data;
    node->hash = hash;

    String_Init(&node->key, NULL);
    String_Swap(&node->key, key);

    return RESULT_OK;
}


Result BucketItem_Init(BucketItem* node,
                       int hash,
                       const char* key,
                       void* data)
{
    Result result = String_Init(&node->key, key);
    node->data = data;
    node->hash = hash;
    return result;
}

Result BucketItem_CreateMoveKey(BucketItem** pp,
                                int hash,
                                String* key,
                                void* data)
{
    Result result = RESULT_OUT_OF_MEM;
    BucketItem* node = (BucketItem*)malloc(sizeof(BucketItem) * 1);
    if (node)
    {
        BucketItem_InitMoveKey(node,
                               hash,
                               key,
                               data);
        *pp = node;
        result = RESULT_OK;
    }
    return result;
}

Result BucketItem_Change(BucketItem* p,
                         void* data)
{
    p->data = data;
    return RESULT_OK;
}

void BucketItem_Destroy(BucketItem* node, void(*pfDestroyData)(void*))
{
    String_Destroy(&node->key);
    if (pfDestroyData)
    {
        pfDestroyData(node->data);
    }
}

void BucketItem_Delete(BucketItem* p, void(*pfDestroyData)(void*))
{
    if (p)
    {
        BucketItem_Destroy(p, pfDestroyData);
        free(p);
    }
}

Result Bucket_Init(Bucket* p, size_t capacity)
{
    Result result = RESULT_OK;
    p->data = NULL;
    p->size = 0;
    p->capacity = 0;

    if (capacity > 0)
    {
        result = Bucket_Reserve(p, capacity);
    }

    return result;
}

Result Bucket_Create(Bucket** pp)
{
    Result result = RESULT_OUT_OF_MEM;
    Bucket*  p = (Bucket*)malloc(sizeof(Bucket) * 1);
    if (p)
    {
        result = Bucket_Init(p, 0);
        if (result == RESULT_OK)
        {
            *pp = p;
            p = NULL;
        }
        free(p);
    }
    return result;
}


void Bucket_Destroy(Bucket* p, void(*pfDestroyData)(void*))
{
    for (size_t i = 0; i < p->size; i++)
    {
        BucketItem_Delete(p->data[i], pfDestroyData);
    }
    free(p->data);
}


void Bucket_Delete(Bucket* p, void(*pfDestroyData)(void*))
{
    if (p)
    {
        Bucket_Destroy(p, pfDestroyData);
        free(p);
    }
}


Result Bucket_Reserve(Bucket* p, size_t nelements)
{
    Result r = RESULT_OK;

    if (nelements > p->capacity)
    {
        BucketItem** pnew = (BucketItem**)realloc(p->data,
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
            ASSERT(false);
            r = RESULT_OUT_OF_MEM;
        }
    }

    return r;
}
static Result Grow(Bucket* p, size_t nelements)
{
    Result r = RESULT_OK;

    if (nelements > p->capacity)
    {
        size_t new_nelements = p->capacity + p->capacity / 2;

        if (new_nelements < nelements)
        {
            new_nelements = nelements;
        }

        r = Bucket_Reserve(p, new_nelements);
    }

    return r;
}

Result Bucket_Append(Bucket* p, BucketItem* pItem)
{
    Result result = Grow(p, p->size + 1);

    if (result == RESULT_OK)
    {
        p->data[p->size] = pItem;
        p->size++;
    }

    return result;
}

static int FindNodeIndex(Bucket* bucket, uint32_t hash, const char* key)
{
    ASSERT(key != NULL);
    for (size_t i = 0; i < bucket->size; i++)
    {
        BucketItem* node = bucket->data[i];
        if (node->hash == hash &&
                strcmp(node->key, key) == 0)
        {
            return (int)i;
        }
    }

    return -1;
}

Result RemoveBucketItem(Bucket* bucket,
                        uint32_t hash,
                        const char* key,
                        void** ppData)
{
    ASSERT(key != NULL);
    *ppData = NULL; //out

    int index = FindNodeIndex(bucket, hash, key);
    Result result = index != -1 ? RESULT_OK : RESULT_FAIL;

    if (result == RESULT_OK)
    {
        //ponteiro de item que vai ser removido (out)
        *ppData = bucket->data[index]->data;

        if (index != (int)(bucket->size) - 1)
        {
            //swap  dos ponteiros de [index] e [size - 1]
            BucketItem* pTemp = bucket->data[bucket->size - 1];
            bucket->data[bucket->size - 1] = bucket->data[index];
            bucket->data[index] = pTemp;
        }

        BucketItem_Delete(bucket->data[bucket->size - 1], NULL);
        bucket->size--;
    }


    return result;
}


Result Buckets_Init(Buckets* p,
                    size_t size)
{
    Result result = RESULT_OUT_OF_MEM;
    p->data = NULL;
    p->size = size;

    p->data = (Bucket**)malloc(sizeof(Bucket*) * size);
    if (p->data)
    {
        for (size_t i = 0; i < size; i++)
        {
            p->data[i] = NULL;
        }
        result = RESULT_OK;
    }

    return result;
}

void Buckets_Destroy(Buckets* p, void(*pfDestroyData)(void*))
{
    for (size_t i = 0; i < p->size; i++)
    {
        Bucket_Delete(p->data[i],
                      pfDestroyData);
    }
    free(p->data);
}


Result Map_Init(Map* map, size_t nBuckets)
{
    map->Size = 0;
    Result result = Buckets_Init(&map->buckets, nBuckets);
    if (result == RESULT_OK)
    {
    }
    return result;
}

Result Map_Create(Map** pp, size_t nBuckets)
{
    Result result = RESULT_OUT_OF_MEM;
    Map* p = (Map*)malloc(sizeof(Map));
    if (p)
    {
        result = Map_Init(p, nBuckets);
        if (result == RESULT_OK)
        {
            *pp = p;
        }
        else
        {
            free(p);
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
    free((void*)p);
}

BucketItem* Map_FindNode(Map* map, const char* key)
{
    if (map->buckets.data == NULL)
    {
        return NULL;
    }

    ASSERT(key != NULL);
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


Result Map_SetMoveKey(Map* map, String* key, void* data)
{
    ASSERT(key != NULL);
    Result result;

    BucketItem* pNode = Map_FindNode(map, *key);
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
        if (result == RESULT_OK)
        {
            map->buckets.data[bucket_n] = bucket;
        }
    }
    else
    {
        result = RESULT_OK;
    }

    if (result == RESULT_OK)
    {
        BucketItem* node;
        result = BucketItem_CreateMoveKey(&node,
                                          hash,
                                          key,
                                          data);
        if (result == RESULT_OK)
        {
            result = Bucket_Append(bucket, node /*moved*/);
        }
    }

    if (result == RESULT_OK)
    {
      map->Size++;
    }

    return result;
}

Result Map_Set(Map* map, const char* key, void* data)
{
    ASSERT(key != NULL);
    void* pv;
    Result result = Map_Find(map, key, &pv);
    if (result == RESULT_OK)
    {
        return RESULT_FAIL;
        //ASSERT(false);
    }


    ASSERT(key != NULL);
    String localkey;
    String_Init(&localkey, key);

    result = Map_SetMoveKey(map, &localkey, data);

    String_Destroy(&localkey);
    return result;
}


Result Map_Find(Map* map, const char* key, void** pp)
{
    ASSERT(key != NULL);
    BucketItem* pNode = Map_FindNode(map, key);
    Result result = pNode ? RESULT_OK : RESULT_FAIL;

    if (result == RESULT_OK)
    {
        *pp = pNode->data;
    }

    return result;
}

void* Map_Find2(Map* map, const char* key)
{
    void* pv;
    Result result = Map_Find(map, key, &pv);

    return result == RESULT_OK ? pv : NULL;
}

Result Map_DeleteEx(Map* map, const char* key, void** pp)
{
    ASSERT(key != NULL);
    uint32_t hash = HashFunc(key);
    int bucket_n = hash % map->buckets.size;

    Bucket* bucket = map->buckets.data[bucket_n];

    if (bucket == NULL)
    {
        return RESULT_FAIL;
    }

    Result result = RemoveBucketItem(bucket, hash, key, pp);

    if (result == RESULT_OK)
    {
      map->Size--;
    }
    return result;
}

Result Map_DeleteItemOpt(Map* map, const char* key, void(*pfDestroyData)(void*))
{
    ASSERT(key != NULL);
    void* p;
    Result result = Map_DeleteEx(map, key, &p);
    if (result == RESULT_OK)
    {
        if (pfDestroyData != NULL)
        {
            pfDestroyData(p);
        }
    }
    return result;
}

Result Map_DeleteItem(Map* map, const char* key, void(*pfDestroyData)(void*))
{
    Result result = Map_DeleteItemOpt(map, key, pfDestroyData);
    void* p;
    //ASSERT(Map_Find(map, key, &p) != RESULT_OK);
    if (Map_Find(map, key, &p) == RESULT_OK)
    {
        ASSERT(false);
        Map_DeleteItemOpt(map, key, pfDestroyData);
    }
    return result;
}


void Map_Print(Map* map)
{
    for (size_t i = 0; i < map->buckets.size; i++)
    {
        Bucket* data = map->buckets.data[i];
        if (data != NULL)
        {
            for (size_t k = 0; k < data->size; k++)
            {
                BucketItem* node = data->data[k];
                printf("%s", node->key);
            }
        }
    }
}


void Buckets_Swap(Buckets* b1, Buckets* b2)
{
    Bucket** data2 = b2->data;
    size_t size2 = b2->size;

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

Result MultiMap_Init(MultiMap* map, size_t nBuckets)
{
  map->Size = 0;
  Result result = Buckets_Init(&map->buckets, nBuckets);
  if (result == RESULT_OK)
  {
  }
  return result;
}

void MultiMap_Destroy(MultiMap* map, void(*pfDestroyData)(void*))
{
  Buckets_Destroy(&map->buckets, pfDestroyData);
}

Result MultiMap_Add(MultiMap* map, const char* key, void* data)
{
  ASSERT(key != NULL);
  Result result;
  
  uint32_t hash = HashFunc(key);
  int bucket_n = hash % map->buckets.size;
  Bucket* bucket = map->buckets.data[bucket_n];

  if (bucket == NULL)
  {
    //Não existia..criar
    result = Bucket_Create(&bucket);
    if (result == RESULT_OK)
    {
      map->buckets.data[bucket_n] = bucket;
    }
  }
  else
  {
    result = RESULT_OK;
  }

  if (result == RESULT_OK)
  {
    //Adiciona no fim - não verifica se ja existe
    String stemp = STRING_INIT;
    String_Set(&stemp, key);
    BucketItem* node;
    result = BucketItem_CreateMoveKey(&node,
      hash,
      &stemp,
      data);

    String_Destroy(&stemp);

    if (result == RESULT_OK)
    {
      result = Bucket_Append(bucket, node /*moved*/);
    }
  }

  if (result == RESULT_OK)
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

  ASSERT(key != NULL);
  uint32_t hash = HashFunc(key);
  size_t bucket_n = hash % map->buckets.size;

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