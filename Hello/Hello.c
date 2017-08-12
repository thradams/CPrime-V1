
#include <stdlib.h>
#include <stdio.h>
#include "Map2.h"



typedef struct User
{
    int i;
    struct User *pNext;
} User;

void User_Delete(User* p);
User* User_Create();


typedef struct Array(User*_auto) UserArray;
typedef struct List(User*_auto)  UserList;
typedef struct Map(User*)  UserMap;


void UserArray_Add(UserArray* users, User* p);
void UserArray_Destroy(UserArray* users);

void UserList_Add(UserList* users, User* p);
void UserList_Destroy(UserList* users);

void UserMap_Destroy(UserMap* users);
void UserMap_Set(UserMap* users, const char* key, User* pUser);
User* UserMap_Lookup(UserMap* users, const char* key);
void UserMap_RemoveKey(UserMap* users, const char* key);


typedef struct
{
    int type _defval( 1);
} Box;

typedef struct
{
    int type _defval( 2);
} Circle;

typedef struct Union(Box, Circle) Shape;

typedef struct
{
    int type _defval(3);
} Button;

typedef struct Union(Shape, Button) Serializable;




int main()
{
    UserArray userArray = { 0 };
    UserList userList = _default{0};
    UserMap userMap = _default{0};

    UserList_Add(&userList, User_Create());

    User* pCurrent = userList.pHead;
    while (pCurrent)
    {
        pCurrent = pCurrent->pNext;
    }


    UserArray_Add(&userArray, User_Create());

    for (int i = 0; i < userArray.Size; i++)
    {
        User *pUser = userArray.pData[i];
    }

    UserMap_Set(&userMap, "a", User_Create());
    User* pUser = UserMap_Lookup(&userMap, "a");
    //UserMap_RemoveKey(&userMap, "a");


    UserArray_Destroy(&userArray);
    UserList_Destroy(&userList);
    UserMap_Destroy(&userMap);
}


int UserArray_Reserve(UserArray* users, int i) _default
{
    int iResult = 0;
    if (i > users->Capacity)
    {
        User** pNew = users->pData;
        pNew = (User**)realloc(pNew, i * sizeof(User*));
        if (pNew != NULL)
        {
            users->pData = pNew;
            users->Capacity = i;
            iResult = i;
        }

    }
    return iResult;
}
void UserArray_Add(UserArray* users, User* p) _default
{
    /*requires*/
    /*int UserArray_Reserve(UserArray* users, int n) default;*/
    if (UserArray_Reserve(users, users->Size + 1) > 0)
    {
        users->pData[users->Size] = p;
        users->Size++;
    }
}
void UserArray_Destroy(UserArray* users) _default
{
    for (int i = 0 ; i < users->Size; i++)
    {
        User_Delete(users->pData[i]);
    }
    free(users->pData);
}
void UserList_Add(UserList* users, User* p) _default
{
    if (users->pHead == NULL)
    {
        users->pHead = p;
    }
    else
    {
        users->pTail->pNext = p;
    }
    users->pTail = p;
}
void UserList_Destroy(UserList* users) _default
{
    User *pItem = users->pHead;
    while (pItem)
    {
        User *pCurrent = pItem;
        pItem = pItem->pNext;
        User_Delete(pCurrent);
    }
}
void UserMap_Destroy(UserMap* users) _default
{
    if (users->pHashTable != NULL)
    {
        for (unsigned int nHash = 0;
           nHash < users->HashTableSize;
           nHash++)
        {
            MapItem2* pKeyValue =
                users->pHashTable[nHash];
        
            while (pKeyValue != NULL)
            {
                MapItem2* pKeyValueCurrent = pKeyValue;
                pKeyValue = pKeyValue->pNext;
                KeyValue_Delete(pKeyValueCurrent);
            }
        }
        
        free(users->pHashTable);
        users->pHashTable = NULL;
        users->Count = 0;
    }
}
void User_Delete(User* p) _default
{
    if (p != NULL) {
        free(p);
    }
}
User* User_Create() _default
{
    User *p = (User*) malloc(sizeof * p);
    if (p != NULL) {
        p->i = 0;
        p->pNext = NULL;
    }
    return p;
}
void UserMap_Set(UserMap* users, const char* key, User* pUser) _default
{
    void* pv;
    Map2_SetAt((Map2*)users, key, pUser, &pv);
    if (pv)
    {
        User_Delete((User*)pv);
    }
}
User* UserMap_Lookup(UserMap* users, const char* key) _default
{
    void* pv;
    if (Map2_Lookup((Map2*)users, key, &pv))
    {
          return (User*)pv;
    }
    return NULL;
}
void UserMap_RemoveKey(UserMap* users, const char* key) _default
{
    void* pv;
    Map2_RemoveKey((Map2*)users, key,  &pv);
    if (pv)
    {
        User_Delete((User*)pv);
    }
}
