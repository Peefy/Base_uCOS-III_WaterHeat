#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "stdint.h"

#include <stdio.h>
#include <stdlib.h>

#define QueueType unsigned char  

#define HaveBool 1

typedef struct
{
    QueueType buffer;
    char data[];
}MyType;  

typedef struct
{
   MyType* qBase;   
   QueueType FrontData; //��ͷԪ��
   int Rear;            //��βָ��
   unsigned int Size;   //���пռ��С
   unsigned int Count;  //����Ԫ�ظ���
}Queue;    

extern Queue* Queue_Byte;

#ifdef HaveBool

#include <stdbool.h>

bool CreateQueue(Queue *pQueue,unsigned int size);
bool InitQueue(Queue *pQueue);
bool IsEmpty(Queue *pQueue);
bool Peek(Queue *pQueue,QueueType *pe);

#else

#define BOOL int
#define TRUE 1
#define FALSE 0

BOOL CreateQueue(Queue *pQueue,unsigned int size);
BOOL InitQueue(Queue *pQueue);
BOOL IsEmpty(Queue *pQueue);
BOOL Peek(Queue *pQueue,QueueType *pe);

#endif

void ClearQueue( Queue *pQueue );
unsigned int GetCount( Queue *pQueue );
unsigned int GetSize(Queue *pQueue);
int IndexOf(Queue *pQueue,QueueType value);
QueueType ValueAt(Queue *pQueue,unsigned int index);
int GetHead(Queue *pQueue);
int Enqueue(Queue *pQueue , QueueType value);
int DeQueue( Queue *pQueue, QueueType *pe );
QueueType GetInQueue(Queue *pQueue);
void Queue_ForEach( Queue *pQueue, void (*func)(QueueType *pe) );

#endif
