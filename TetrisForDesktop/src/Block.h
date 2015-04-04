#ifndef _BLOCK_H
#define _BLOCK_H

typedef struct _point{
	int x;
	int y;
}Point;

#define POSITIONS_SIZE 4

typedef struct _block{
	Point positions[POSITIONS_SIZE][POSITIONS_SIZE];
	int current;
	int next;
	int direction;
}Block;

Block Block_Make(int isFirst, Block block);
Block Block_Move(Block block, int direction);
Point* Block_GetPositions(Block block);
void Block_PrintNext(Block block, int x, int y);

#endif