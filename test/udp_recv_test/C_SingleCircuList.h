#pragma once
#include <iostream>
typedef unsigned int UINT32;

#include "st_MSG.h"

using namespace std;

typedef struct queue
{
	_DATA *pBase;
	int front;    //ָ����е�һ��Ԫ��
	int rear;    //ָ��������һ��Ԫ�ص���һ��Ԫ��
	int maxsize; //ѭ�����е����洢�ռ�
}QUEUE, *PQUEUE;

void CreateQueue(PQUEUE Q, int maxsize);

bool FullQueue(PQUEUE Q);
bool EmptyQueue(PQUEUE Q);

bool Enqueue(PQUEUE Q, _DATA* data);
bool Dequeue(PQUEUE Q, _DATA *data);

bool Clequeue(PQUEUE Q);
