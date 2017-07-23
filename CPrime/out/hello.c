typedef struct
{
    int type /* =   1 */;
    int w;
    int h;
} Box;

void Box_Init(Box* pBox)  /*default*/
{pBox->type =   1;
pBox->w = 0;
pBox->h = 0;

}

Box* Box_Create()  /*default*/
{

Box *p = malloc(sizeof * p);
if (p != NULL) {
Box_Init(p);
}
return p;

}
void Box_Delete(Box* p)  /*default*/
{if (p != NULL) {
free(p);
}

}

typedef struct  {Box** pHead, *pTail;} Boxes;

void Boxes_Add(Boxes* p, Box* pItem)  /*default*/
{
    if (pList->pHead == NULL) {
        pList->pHead = pItem; 
    }
    else
    {
        pList->pTail->pNext = pItem; 
    }
    pList->pTail = pItem; 

}
//void Boxes_Init(Boxes* p) default;
//void Boxes_Destroy(Boxes* p) default;

typedef struct
{
    Boxes boxes;
} Z;
void Z_Init(Z* p)  /*default*/
{p->boxes->pHead = NULL;
p->boxes->pTail = NULL;

}
void Z_Destroy(Z* p)  /*default*/
{Box* *pItem = p->boxes->pHead;
while (pItem)
{
  Box** pCurrent = pItem;
  pItem = pItem->pNext;
  Box*_Delete(pCurrent);
}

}