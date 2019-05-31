#pragma once
#pragma source


#include <inttypes.h>
#include <stdbool.h>
#include "StringEx.h"

struct BucketItem
{
    char* /*@auto*/ key;
    void* data;
    uint32_t hash;
};
#define BUCKET_ITEM_INIT { NULL, NULL, 0 }

struct Bucket
{
    struct BucketItem** data;
    int size;
    int capacity;
};
#define BUCKET_INIT {NULL , 0,0 }

struct Buckets
{
    struct Bucket** data;
    int size;
};
#define BUCKETS_INIT { NULL, 0}

struct Map
{
    struct Buckets buckets;
    int Size;
};

#define MAP_INIT {BUCKETS_INIT, 0}

bool Map_Init(struct Map* map, int nBuckets);

void Map_Swap(struct Map* map, struct Map* map2);

void Map_Destroy(struct Map* map, void(*pfDestroyData)(void*));

void Map_Delete(struct Map* map, void(*pfDestroyData)(void*));
bool Map_Create(struct Map** map, int nBuckets);

bool Map_Set(struct Map* map, const char* key, void* data);
bool Map_SetMoveKey(struct Map* map, char** key, void* data);

bool Map_Find(struct Map* map, const char* key, void** pp);
void* Map_Find2(struct Map* map, const char* key);
bool Map_DeleteItem(struct Map* map, const char* key, void(*pfDestroyData)(void*));
bool Map_DeleteItemOpt(struct Map* map, const char* key, void(*pfDestroyData)(void*));

void Map_Print(struct Map* map);





//////////////
typedef struct
{
    struct Buckets buckets;
    int Size;
} MultiMap;

#define MULTIMAP_INIT {BUCKETS_INIT, 0}

bool MultiMap_Init(MultiMap* map, int nBuckets);
void MultiMap_Destroy(MultiMap* map, void(*pfDestroyData)(void*));

//Adiciona outro item no mapa sem testar se ja existe
bool MultiMap_Add(MultiMap* map, const char* key, void* data);

//Retorna todo bucket que tem o mesm hash
//Ainda é preciso percorrer para saber se sao da mesma key
//Varias entradas para mesma key
struct Bucket* MultiMap_FindBucket(MultiMap* map, const char* key);
void MultiMap_Swap(MultiMap* map, MultiMap* map2);


