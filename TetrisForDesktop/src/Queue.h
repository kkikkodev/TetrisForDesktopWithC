#ifndef	_QUEUE_H
#define	_QUEUE_H

#include "Array.h"

typedef struct _queue{
	Array data;
	int capacity;
	int rear;
}Queue;

void Queue_Create(Queue* queue, int capacity, size_t size);
void Queue_Destroy(Queue* queue);
int Queue_Put(Queue* queue, void* object, size_t size);
void Queue_Get(Queue* queue, void* object, size_t size);
void Queue_At(Queue* queue, void* object, int index, size_t size);
int Queue_IsEmpty(Queue* queue);
int Queue_IsFull(Queue* queue);

#endif