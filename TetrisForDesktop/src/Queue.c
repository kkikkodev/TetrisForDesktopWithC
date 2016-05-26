#include "Queue.h"
#include <string.h>

void Queue_Create(Queue* queue, int capacity, size_t size){
	Array_Create(&(queue->data), capacity, size);
	queue->capacity = queue->data.capacity;
	queue->rear = -1;
}

void Queue_Destroy(Queue* queue){
	Array_Destroy(&(queue->data));
}

int Queue_Put(Queue* queue, void* object, size_t size){
	int index;
	if (!Queue_IsFull(queue)){
		index = Array_Store(&(queue->data), queue->rear + 1, object, size);
	}
	else{
		index = Array_AppendFromRear(&(queue->data), object, size);
		queue->capacity++;
	}
	if (index != -1){
		queue->rear++;
	}
	return queue->rear;
}

void Queue_Get(Queue* queue, void* object, size_t size){
	int index;
	if (Queue_IsEmpty(queue)){
		memset(object, 0, size);
	}
	else{
		Array_GetAt(&(queue->data), 0, object, size);
		index = Array_DeleteFromFront(&(queue->data), size);
		if (index == -1){
			queue->capacity--;
			queue->rear--;
		}
	}
}

void Queue_At(Queue* queue, void* object, int index, size_t size){
	if (Queue_IsEmpty(queue)){
		memset(object, 0, size);
	}
	else{
		Array_GetAt(&(queue->data), index, object, size);
	}
}

int Queue_IsEmpty(Queue* queue){
	return queue->rear == -1;
}

int Queue_IsFull(Queue* queue){
	return queue->rear >= queue->capacity - 1;
}

//다음블럭과 다다음블럭 바꾸기
void Queue_Modify(Queue* queue, void* object, int index, size_t size){
	//index번지의 값을 object로 수정
	Array_Modify(&(queue->data), index, object, size);
}