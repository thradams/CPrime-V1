#pragma once


#define ForEachListItem(T, var, list)\
  for (T * var = (list)->pHead ; var != NULL; var =  var->pNext)

#define List_IsFirstItem(pList, pItem) ((pList)->pHead == (pItem))
#define List_IsLastItem(pList, pItem) ((pList)->pTail == (pItem))
