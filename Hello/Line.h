#pragma once

typedef struct Point
{
    int x _defval(1);
    int y;
} Point;

typedef struct
{
    Point start;
    Point end;
} Line;

//void Line_Delete(Line* p);
Line* Line_Create();

typedef struct Array(Line*_auto) { Line**pData; int Size, Capacity; }  Lines;

void Lines_Add(Lines* pLines, Line* pLine);
void Lines_Init(Lines* pLines);
void Lines_Destroy(Lines* pLines);
    //
