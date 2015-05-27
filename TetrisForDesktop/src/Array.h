#ifndef	_ARRAY_H
#define	_ARRAY_H

#include <stddef.h>												

typedef struct _array{
	void* front;
	int capacity;
	int length;
	int current;
}Array;

void Array_Create(Array* array, int capacity, size_t size);
void Array_Destroy(Array* array);
int Array_Store(Array* array, int index, void* object, size_t size);
int Array_Insert(Array* array, int index, void* object, size_t size);
int Array_AppendFromFront(Array* array, void* object, size_t size);
int Array_AppendFromRear(Array* array, void* object, size_t size);
int Array_Delete(Array* array, int index, size_t size);
int Array_DeleteFromFront(Array* array, size_t size);
int Array_DeleteFromRear(Array* array, size_t size);
void Array_Clear(Array* array);
int Array_Modify(Array* array, int index, void* object, size_t size);
int Array_LinearSearchByUnique(Array* array, void* key, size_t size, int(*Compare)(void*, void*));
void Array_LinearSearchByDuplicate(Array* array, void* key, int** indexes, int* count, size_t size, int(*Compare)(void*, void*));
int Array_BinarySearchByUnique(Array* array, void* key, size_t size, int(*Compare)(void*, void*));
void Array_BinarySearchByDuplicate(Array* array, void* key, int** indexes, int* count, size_t size, int(*Compare)(void*, void*));
void Array_SelectionSort(Array* array, size_t size, int(*Compare)(void*, void*));
void Array_InsertionSort(Array* array, size_t size, int(*Compare)(void*, void*));
void Array_Indirect_InsertionSort(Array* array, int** indexes, size_t size, int(*Compare)(void*, void*));
void Array_GetAt(Array* array, int index, void* object, size_t size);

#endif	