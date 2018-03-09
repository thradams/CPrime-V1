#include "config.h"



//#include "stdafx.h"
//#include <stdio.h>
//#include <stdlib.h>

void Connect(void(*PF)(void*), void* data)
{
  PF(data);
}

void Login(void(*PF)(void*), void* data)
{
  PF(data);
}

void Read(void(*PF)(void*), void* data)
{
  PF(data);
}


typedef struct { int i; } MyTask;




int main()
{
	MyTask* p = (MyTask*)malloc(sizeof * p);
	p->i = 123;
	Connect([](void* p)
	{
		MyTask* pTask = (MyTask*)p;
		printf("connect %d", pTask->i);

		Login([](void* p)
		{
			MyTask* pTask = (MyTask*)p;
			printf("%d", pTask->i);

			Read([](void* p)
			{
				MyTask* pTask = (MyTask*)p;
				printf("%d", pTask->i);
				free(pTask);
			}, p);
		}, p);
	}, p);

	return 0;
}
