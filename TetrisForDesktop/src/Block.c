#include <time.h>
#include <windows.h>
#include <stdio.h>
#include "Block.h"
#include "Util.h"
#include "Constant.h"

#define NEXT_QUEUE_SIZE 2
#define BLOCK_EXAMPLES_SIZE 7

const static Point blockExamples[BLOCK_EXAMPLES_SIZE][POSITIONS_SIZE][POSITIONS_SIZE] = {
	//仃仃仃仃
	{
		{ { 0, 5 }, { 0, 6 }, { 0, 7 }, { 0, 8 } },
		{ { -1, 6 }, { 0, 6 }, { 1, 6 }, { 2, 6 } },
		{ { 0, 5 }, { 0, 6 }, { 0, 7 }, { 0, 8 } },
		{ { -1, 6 }, { 0, 6 }, { 1, 6 }, { 2, 6 } }
	},
	//    仃
	//仃仃仃
	{
		{ { 0, 8 }, { 1, 6 }, { 1, 7 }, { 1, 8 } },
		{ { -1, 7 }, { 0, 7 }, { 1, 7 }, { 1, 8 } },
		{ { 0, 6 }, { 0, 7 }, { 0, 8 }, { 1, 6 } },
		{ { -1, 6 }, { -1, 7 }, { 0, 7 }, { 1, 7 } }
	},
	//  仃仃
	//仃仃
	{
		{ { 0, 7 }, { 0, 8 }, { 1, 6 }, { 1, 7 } },
		{ { -1, 6 }, { 0, 6 }, { 0, 7 }, { 1, 7 } },
		{ { 0, 7 }, { 0, 8 }, { 1, 6 }, { 1, 7 } },
		{ { -1, 6 }, { 0, 6 }, { 0, 7 }, { 1, 7 } }
	},
	//仃仃
	//  仃仃
	{
		{ { 0, 6 }, { 0, 7 }, { 1, 7 }, { 1, 8 } },
		{ { -1, 8 }, { 0, 8 }, { 0, 7 }, { 1, 7 } },
		{ { 0, 6 }, { 0, 7 }, { 1, 7 }, { 1, 8 } },
		{ { -1, 8 }, { 0, 8 }, { 0, 7 }, { 1, 7 } }
	},
	//  仃
	//仃仃仃
	{
		{ { 0, 7 }, { 1, 6 }, { 1, 7 }, { 1, 8 } },
		{ { -1, 7 }, { 0, 7 }, { 0, 8 }, { 1, 7 } },
		{ { 0, 6 }, { 0, 7 }, { 0, 8 }, { 1, 7 } },
		{ { -1, 7 }, { 0, 6 }, { 0, 7 }, { 1, 7 } }
	},
	//仃
	//仃仃仃
	{
		{ { 0, 6 }, { 1, 6 }, { 1, 7 }, { 1, 8 } },
		{ { -1, 8 }, { -1, 7 }, { 0, 7 }, { 1, 7 } },
		{ { 0, 6 }, { 0, 7 }, { 0, 8 }, { 1, 8 } },
		{ { -1, 7 }, { 0, 7 }, { 1, 7 }, { 1, 6 } }
	},
	//仃仃
	//仃仃
	{
		{ { 0, 6 }, { 0, 7 }, { 1, 6 }, { 1, 7 } },
		{ { 0, 6 }, { 0, 7 }, { 1, 6 }, { 1, 7 } },
		{ { 0, 6 }, { 0, 7 }, { 1, 6 }, { 1, 7 } },
		{ { 0, 6 }, { 0, 7 }, { 1, 6 }, { 1, 7 } }
	}
};

static Block _Block_MoveToDown(Block block);
static Block _Block_MoveToLeft(Block block);
static Block _Block_MoveToRight(Block block);
static Block _Block_RotateRight(Block block);
static void _Block_PrintDefaultBlock(int blockNumber, int x, int* y);

Block Block_Make(int isFirst, Block block){
	int i;
	int j;
	int next1;
	int next2;
	srand((unsigned int)time(NULL));
	if (isFirst){
		block.current = rand() % BLOCK_EXAMPLES_SIZE;
		block.hold = -1;
	}
	else{
		Queue_Get(&block.next, &block.current, sizeof(int));
	}
	for (i = 0; i < POSITIONS_SIZE; i++){
		for (j = 0; j < POSITIONS_SIZE; j++){
			block.positions[i][j] = blockExamples[block.current][i][j];
		}
	}
	if (isFirst){
		Queue_Create(&block.next, NEXT_QUEUE_SIZE, sizeof(int));
		do{
			next1 = rand() % BLOCK_EXAMPLES_SIZE;
		} while (block.current == next1);
		Queue_Put(&block.next, &next1, sizeof(int));
	}
	Queue_At(&block.next, &next1, 0, sizeof(int));
	do{
		next2 = rand() % BLOCK_EXAMPLES_SIZE;
	} while (block.current == next2 || next1 == next2);
	Queue_Put(&block.next, &next2, sizeof(int));
	block.direction = UP;
	block.color = rand() % (FONT_COLOR_SIZE - 2) + 2;
	return block;
}

void Block_Destroy(Block block){
	Queue_Destroy(&block.next);
}

Block Block_Move(Block block, int direction){
	switch (direction){
	case LEFT:
		return _Block_MoveToLeft(block);
	case RIGHT:
		return _Block_MoveToRight(block);
	case DOWN:
		return _Block_MoveToDown(block);
	case UP:
		return _Block_RotateRight(block);
	}
	return _Block_MoveToDown(block);
}

Point* Block_GetPositions(Block block){
	return block.positions[block.direction];
}

int Block_IsHoldSet(Block block){
	return block.hold != -1;
}

void Block_ChangeCurrentForHold(Block* block){
	int i;
	int j;
	int temp = block->current;
	block->current = block->hold;
	block->hold = temp;
	if (block->current != -1){
		for (i = 0; i < POSITIONS_SIZE; i++){
			for (j = 0; j < POSITIONS_SIZE; j++){
				block->positions[i][j] = blockExamples[block->current][i][j];
			}
		}
	}
	else{
		*block = Block_Make(False, *block);
	}
}

void Block_PrintNext(Block block, int index, int x, int y){
	int next;
	CursorUtil_GotoXY(x, y++);
	printf("旨收 Next %d 收旬", index + 1);
	CursorUtil_GotoXY(x, y++);
	Queue_At(&block.next, &next, index, sizeof(int));
	_Block_PrintDefaultBlock(next, x, &y);
	CursorUtil_GotoXY(x, y++);
	printf("曲收收收收收收旭");
}

void Block_PrintHold(Block block, int x, int y){
	CursorUtil_GotoXY(x, y++);
	printf("旨收  Hold  收旬");
	CursorUtil_GotoXY(x, y++);
	_Block_PrintDefaultBlock(block.hold, x, &y);
	CursorUtil_GotoXY(x, y++);
	printf("曲收收收收收收旭");
}

static Block _Block_MoveToDown(Block block){
	int i;
	int j;
	for (i = 0; i < POSITIONS_SIZE; i++){
		for (j = 0; j < POSITIONS_SIZE; j++){
			block.positions[i][j].x++;
		}
	}
	return block;
}

static Block _Block_MoveToLeft(Block block){
	int i;
	int j;
	for (i = 0; i < POSITIONS_SIZE; i++){
		for (j = 0; j < POSITIONS_SIZE; j++){
			block.positions[i][j].y--;
		}
	}
	return block;
}

static Block _Block_MoveToRight(Block block){
	int i;
	int j;
	for (i = 0; i < POSITIONS_SIZE; i++){
		for (j = 0; j < POSITIONS_SIZE; j++){
			block.positions[i][j].y++;
		}
	}
	return block;
}

static Block _Block_RotateRight(Block block){
	block.direction = (block.direction + 1) % POSITIONS_SIZE;
	return block;
}

static void _Block_PrintDefaultBlock(int blockNumber, int x, int* y){
	switch (blockNumber){
	case -1:
		printf("早            早");
		CursorUtil_GotoXY(x, (*y)++);
		printf("早            早");
		break;
	case 0:
		printf("早  ﹥﹥﹥﹥  早");
		CursorUtil_GotoXY(x, (*y)++);
		printf("早            早");
		break;
	case 1:
		printf("早       ﹥   早");
		CursorUtil_GotoXY(x, (*y)++);
		printf("早   ﹥﹥﹥   早");
		break;
	case 2:
		printf("早     ﹥﹥   早");
		CursorUtil_GotoXY(x, (*y)++);
		printf("早   ﹥﹥     早");
		break;
	case 3:
		printf("早   ﹥﹥     早");
		CursorUtil_GotoXY(x, (*y)++);
		printf("早     ﹥﹥   早");
		break;
	case 4:
		printf("早     ﹥     早");
		CursorUtil_GotoXY(x, (*y)++);
		printf("早   ﹥﹥﹥   早");
		break;
	case 5:
		printf("早   ﹥       早");
		CursorUtil_GotoXY(x, (*y)++);
		printf("早   ﹥﹥﹥   早");
		break;
	case 6:
		printf("早    ﹥﹥    早");
		CursorUtil_GotoXY(x, (*y)++);
		printf("早    ﹥﹥    早");
		break;
	}
}