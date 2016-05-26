#ifndef _BLOCK_H
#define _BLOCK_H

#include "Point.h"
#include "Queue.h"

#define POSITIONS_SIZE 4

typedef struct _block{
	Point positions[POSITIONS_SIZE][POSITIONS_SIZE];
	int current;
	Queue next;
	int hold;
	int direction;
	int color;
}Block;

Block Block_Make(int isFirst, Block block);
void Block_Destroy(Block block);
Block Block_Move(Block block, int direction);
Point* Block_GetPositions(Block block);
void Block_ChangeCurrentForHold(Block* block);
void Block_PrintNext(Block block, int index, int x, int y);
void Block_PrintHold(Block block, int x, int y);

//다음 블럭과 다다음 블럭 바꾸기
void Block_ChangeNext(Block block);

//다음 블럭 숨기기
void Block_BlindNext(Block block, int index, int x, int y);

#endif