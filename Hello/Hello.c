
#include <stdlib.h>
#include <stdio.h>

typedef struct MapItem2
{
    struct MapItem2* pNext;
    unsigned int HashValue;
    const char* Key;
    void* pValue;
} MapItem2;

typedef struct User
{
    int i;
    struct User *pNext;
} User;

void User_Delete(User* p);
User* User_Create();


typedef struct Array(User*_auto) UserArray;
typedef struct List(User*_auto)  UserList;
typedef struct Map(User*_auto)  UserMap;

void UserArray_Add(UserArray* users, User* p);
void UserArray_Destroy(UserArray* users);

void UserList_Add(UserList* users, User* p);
void UserList_Destroy(UserList* users);

void UserMap_Destroy(UserMap* users);


int main()
{
    UserArray userArray = _default{NULL, 0, 0};
    UserList userList = _default{NULL, NULL};
    UserMap userMap = _default{NULL, 0, 0};

    User* pCurrent = userList.pHead;
    while (pCurrent)
    {
        pCurrent = pCurrent->pNext;
    }

    UserList_Add(&userList, User_Create());
    UserArray_Add(&userArray, User_Create());



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
    
    if (users->pHead == NULL) {
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
    }
    return p;
}
