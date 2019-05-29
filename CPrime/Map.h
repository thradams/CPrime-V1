#pragma once
#pragma source


#include <inttypes.h>
#include <stdbool.h>
#include "StringEx.h"

struct BucketItem
{
    String * /*@auto*/ key;
    void * data;
    uint32_t hash;
};
#define BUCKET_ITEM_INIT { NULL, NULL, 0 }

typedef struct
{
    struct BucketItem ** data;
    int size;
    int capacity;

} Bucket;
#define BUCKET_INIT {NULL , 0,0 }

typedef struct
{
    Bucket ** data;
    int size;
} Buckets;
#define BUCKETS_INIT { NULL, 0}

typedef struct
{
    Buckets buckets;
    int Size;
} Map;

#define MAP_INIT {BUCKETS_INIT, 0}

bool Map_Init(Map * map, int nBuckets);

void Map_Swap(Map * map, Map * map2);

void Map_Destroy(Map * map, void(*pfDestroyData)(void *));

void Map_Delete(Map * map, void(*pfDestroyData)(void *));
bool Map_Create(Map ** map, int nBuckets);

bool Map_Set(Map * map, const char * key, void * data);
bool Map_SetMoveKey(Map * map, String ** key, void * data);

bool Map_Find(Map * map, const char * key, void ** pp);
void * Map_Find2(Map * map, const char * key);
bool Map_DeleteItem(Map * map, const char * key, void(*pfDestroyData)(void *));
bool Map_DeleteItemOpt(Map * map, const char * key, void(*pfDestroyData)(void *));

void Map_Print(Map * map);





//////////////
typedef struct
{
    Buckets buckets;
    int Size;
} MultiMap;

#define MULTIMAP_INIT {BUCKETS_INIT, 0}

bool MultiMap_Init(MultiMap * map, int nBuckets);
void MultiMap_Destroy(MultiMap * map, void(*pfDestroyData)(void *));

//Adiciona outro item no mapa sem testar se ja existe
bool MultiMap_Add(MultiMap * map, const char * key, void * data);

//Retorna todo bucket que tem o mesm hash
//Ainda é preciso percorrer para saber se sao da mesma key
//Varias entradas para mesma key
Bucket * MultiMap_FindBucket(MultiMap * map, const char * key);
void MultiMap_Swap(MultiMap * map, MultiMap * map2);


