#include "Queue.h"
#include <string.h>

void Queue_Create(Queue* queue, int capacity, size_t size){ //큐 생성
	Array_Create(&(queue->data), capacity, size); // 배열을 사용하여 큐를 생성
	queue->capacity = queue->data.capacity;
	queue->rear = -1; // 현재 아무 값이 없음을 의미
}

void Queue_Destroy(Queue* queue){ // 큐를 제거
	Array_Destroy(&(queue->data));
}

int Queue_Put(Queue* queue, void* object, size_t size){ //큐에 값을 입력
	int index;
	if (!Queue_IsFull(queue)){ //가득 찼을 경우
		index = Array_Store(&(queue->data), queue->rear + 1, object, size);
	}
	else{
		index = Array_AppendFromRear(&(queue->data), object, size); //현재 위치 다음 Index에 저장
		queue->capacity++;
	}
	if (index != -1){//큐에 값이 들어갔다면 현재 위치를 변경 해줌
		queue->rear++; 
	}
	return queue->rear;
}

void Queue_Get(Queue* queue, void* object, size_t size){ //큐 값을 하나 가져옴
	int index;
	if (Queue_IsEmpty(queue)){ //큐에 값이 없을 경우
		memset(object, 0, size);
	}
	else{
		Array_GetAt(&(queue->data), 0, object, size);
		index = Array_DeleteFromFront(&(queue->data), size); //제일 앞에 있는 값부터 출력
		if (index == -1){ 
			queue->capacity--;
			queue->rear--;
		}
	}
}

void Queue_At(Queue* queue, void* object, int index, size_t size){ //큐 검색
	if (Queue_IsEmpty(queue)){
		memset(object, 0, size);
	}
	else{
		Array_GetAt(&(queue->data), index, object, size);
	}
}

int Queue_IsEmpty(Queue* queue){ //큐의 상태가 비어 있는지 확인
	return queue->rear == -1;
}

int Queue_IsFull(Queue* queue){ //꽉찬 큐인지 확인
	return queue->rear >= queue->capacity - 1;
}