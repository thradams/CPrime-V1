#pragma once

#pragma once

#include <inttypes.h>
#include "Result.h"
#include "StringEx.h"

typedef struct
{
    String key;
    void *data;
    uint32_t hash;
} BucketItem;
#define BUCKET_ITEM_INIT { STRING_INIT, NULL, 0 }

typedef struct
{
    BucketItem** data;
    size_t size;
    size_t capacity;

} Bucket;
#define BUCKET_INIT {NULL , 0,0 }

typedef struct
{
    Bucket** data;
    size_t size;
} Buckets;
#define BUCKETS_INIT { NULL, 0}

typedef struct
{
    Buckets buckets;
    int Size;
} Map;

#define MAP_INIT {BUCKETS_INIT, 0}

Result Map_Init(Map* map, size_t nBuckets);

void Map_Swap(Map* map, Map* map2);

void Map_Destroy(Map *map, void(*pfDestroyData)(void*));

void Map_Delete(Map *map, void(*pfDestroyData)(void*));
Result Map_Create(Map **map, size_t nBuckets);

Result Map_Set(Map *map, const char*key, void *data);
Result Map_SetMoveKey(Map* map, String* key, void* data);

Result Map_Find(Map* map, const char* key, void** pp);
void* Map_Find2(Map* map, const char* key);
Result Map_DeleteItem(Map *map, const char* key, void(*pfDestroyData)(void*));
Result Map_DeleteItemOpt(Map* map, const char* key, void(*pfDestroyData)(void*));

void Map_Print(Map *map);





//////////////
typedef struct
{
  Buckets buckets;
  int Size;
} MultiMap;

#define MULTIMAP_INIT {BUCKETS_INIT, 0}

Result MultiMap_Init(MultiMap* map, size_t nBuckets);
void MultiMap_Destroy(MultiMap *map, void(*pfDestroyData)(void*));

//Adiciona outro item no mapa sem testar se ja existe
Result MultiMap_Add(MultiMap *map, const char*key, void *data);

//Retorna todo bucket que tem o mesm hash
//Ainda é preciso percorrer para saber se sao da mesma key
//Varias entradas para mesma key
Bucket* MultiMap_FindBucket(MultiMap* map, const char* key);
void MultiMap_Swap(MultiMap* map, MultiMap* map2);


