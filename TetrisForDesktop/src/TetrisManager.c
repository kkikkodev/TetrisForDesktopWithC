#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "TetrisManager.h"
#include "Util.h"
#include "Constant.h"

#define INITAL_SPEED 500
#define SPEED_LEVEL_OFFSET 100
#define LEVELP_UP_CONDITION 3
#define STATUS_POSITION_X_TO_PRINT 40
#define STATUS_POSITION_Y_TO_PRINT 6

static void _TetrisManager_ClearBoard(TetrisManager* tetrisManager);
static void _TetrisManager_ChangeBoardByStatus(TetrisManager* tetrisManager, int status);
static void _TetrisManager_UpSpeedLevel(TetrisManager* tetrisManager);
static void _TetrisManager_SearchLineIndexesToDelete(TetrisManager* tetrisManager, int* indexes, int* count);
static void _TetrisManager_DeleteLines(TetrisManager* tetrisManager, int* indexes, int count);

void TetrisManager_Init(TetrisManager* tetrisManager, int speedLevel){
	Block block;
	block.current = -1;
	memset(tetrisManager->board, 0, sizeof(char)* BOARD_ROW_SIZE * BOARD_COL_SIZE);
	_TetrisManager_ClearBoard(tetrisManager);
	tetrisManager->block = Block_Make(True, block);
	tetrisManager->deletedLineCount = 0;
	tetrisManager->speedLevel = speedLevel;
}

int TetrisManager_CheckValidPosition(TetrisManager* tetrisManager, int direction){
	Block temp = Block_Move(tetrisManager->block, direction);
	int i;
	for (i = 0; i < POSITIONS_SIZE; i++){
		int x = Block_GetPositions(temp)[i].x;
		int y = Block_GetPositions(temp)[i].y;
		if (tetrisManager->board[x][y] != EMPTY && tetrisManager->board[x][y] != MOVING_BLOCK){
			return tetrisManager->board[x][y];
		}
	}
	return EMPTY;
}

void TetrisManager_ChangeBoardByDirection(TetrisManager* tetrisManager, int direction){
	int tempDirection = DOWN;
	int tempCheckResult = EMPTY;
	_TetrisManager_ClearBoard(tetrisManager);
	int checkResult = TetrisManager_CheckValidPosition(tetrisManager, direction);
	if (checkResult == EMPTY){
		tetrisManager->block = Block_Move(tetrisManager->block, direction);
	}
	else{
		if (direction == UP){
			switch (checkResult){
			case TOP_WALL:
				tempDirection = DOWN;
				tempCheckResult = TOP_WALL;
				break;
			case RIGHT_WALL:
				tempDirection = LEFT;
				tempCheckResult = RIGHT_WALL;
				break;
			case LEFT_WALL:
				tempDirection = RIGHT;
				tempCheckResult = LEFT_WALL;
				break;
			}
			do{
				tetrisManager->block = Block_Move(tetrisManager->block, tempDirection);
			} while (TetrisManager_CheckValidPosition(tetrisManager, direction) == tempCheckResult);
			tetrisManager->block = Block_Move(tetrisManager->block, direction);
		}
		else{
			if (direction == RIGHT && checkResult == RIGHT_WALL ||
				direction == LEFT && checkResult == LEFT_WALL || 
				direction == RIGHT && checkResult == FIXED_BLOCK ||
				direction == LEFT && checkResult == FIXED_BLOCK){
				TetrisManager_Sleep(tetrisManager);
				tetrisManager->block = Block_Move(tetrisManager->block, DOWN);
			}
		}
	}
	_TetrisManager_ChangeBoardByStatus(tetrisManager, MOVING_BLOCK);
}

void TetrisManager_ChangeBoardByAuto(TetrisManager* tetrisManager){
	TetrisManager_ChangeBoardByDirection(tetrisManager, DOWN);
}

void TetrisManager_ProcessDirectDown(TetrisManager* tetrisManager){
	while (!TetrisManager_IsReachedToBottom(tetrisManager)){
		TetrisManager_ChangeBoardByDirection(tetrisManager, DOWN);
	}
}

void TetrisManager_ProcessDeletingLines(TetrisManager* tetrisManager){
	int indexes[BOARD_ROW_SIZE];
	int count;
	int i;
	_TetrisManager_SearchLineIndexesToDelete(tetrisManager, indexes, &count);
	if (count > 0){
		_TetrisManager_DeleteLines(tetrisManager, indexes, count);
		for (i = tetrisManager->speedLevel; i <= tetrisManager->deletedLineCount / LEVELP_UP_CONDITION; i++){
			_TetrisManager_UpSpeedLevel(tetrisManager);
		}
	}
}

int TetrisManager_IsReachedToBottom(TetrisManager* tetrisManager){
	int i;
	for (i = 0; i < POSITIONS_SIZE; i++){
		int x = Block_GetPositions(tetrisManager->block)[i].x;
		int y = Block_GetPositions(tetrisManager->block)[i].y;
		if (tetrisManager->board[x + 1][y] != EMPTY && tetrisManager->board[x + 1][y] != MOVING_BLOCK){
			return True;
		}
	}
	return False;
}

int TetrisManager_ProcessReachedCase(TetrisManager* tetrisManager){
	_TetrisManager_ChangeBoardByStatus(tetrisManager, FIXED_BLOCK);
	tetrisManager->block = Block_Make(False, tetrisManager->block);
	if (TetrisManager_IsReachedToBottom(tetrisManager)){
		return END;
	}
	else{
		return PLAYING;
	}
}

void TetrisManager_Sleep(TetrisManager* tetrisManager){
	int i;
	DWORD milliSecond = INITAL_SPEED;
	for (i = MIN_SPEED_LEVEL; i < tetrisManager->speedLevel; i++){
		if (i < MAX_SPEED_LEVEL / 2){
			milliSecond -= SPEED_LEVEL_OFFSET;
		}
		else{
			milliSecond -= (SPEED_LEVEL_OFFSET / 5);
		}
	}
	Sleep(milliSecond);
}

void TetrisManager_Print(TetrisManager* tetrisManager){
	int i;
	int j;
	CursorUtil_GotoXY(0, 0);
	for (i = 0; i < BOARD_ROW_SIZE; i++){
		for (j = 0; j < BOARD_COL_SIZE; j++){
			switch (tetrisManager->board[i][j]){
			case LEFT_TOP_EDGE:
				printf("¦Ç");
				break;
			case RIGHT_TOP_EDGE:
				printf("¦Á");
				break;
			case LEFT_BOTTOM_EDGE:
				printf("¦Å");
				break;
			case RIGHT_BOTTOM_EDGE:
				printf("¦Ã");
				break;
			case EMPTY:
				printf("  ");
				break;
			case MOVING_BLOCK:
				printf("¡á");
				break;
			case FIXED_BLOCK:
				printf("¢Ê");
				break;
			case LEFT_WALL:
			case RIGHT_WALL:
				printf("£ü");
				break;
			case TOP_WALL:
			case BOTTOM_WALL:
				printf("¡ª");
				break;
			}
		}
		printf("\n");
	}
	CursorUtil_GotoXY(STATUS_POSITION_X_TO_PRINT, STATUS_POSITION_Y_TO_PRINT);
	printf("***** Tetris *****\n");
	CursorUtil_GotoXY(STATUS_POSITION_X_TO_PRINT, STATUS_POSITION_Y_TO_PRINT + 1);
	printf("Current speed level : %d level\n", tetrisManager->speedLevel);
	CursorUtil_GotoXY(STATUS_POSITION_X_TO_PRINT, STATUS_POSITION_Y_TO_PRINT + 2);
	printf("Deleted lines : %d lines", tetrisManager->deletedLineCount);
	Block_PrintNext(tetrisManager->block, STATUS_POSITION_X_TO_PRINT, STATUS_POSITION_Y_TO_PRINT + 4);
	CursorUtil_Hide();
}

static void _TetrisManager_ClearBoard(TetrisManager* tetrisManager){
	int i;
	int j;
	for (i = 0; i < BOARD_ROW_SIZE; i++){
		tetrisManager->board[i][0] = LEFT_WALL;
		tetrisManager->board[i][BOARD_COL_SIZE - 1] = RIGHT_WALL;
	}
	for (i = 0; i < BOARD_COL_SIZE; i++){
		tetrisManager->board[0][i] = TOP_WALL;
		tetrisManager->board[BOARD_ROW_SIZE - 1][i] = BOTTOM_WALL;
	}
	for (i = 1; i < BOARD_ROW_SIZE - 1; i++){
		for (j = 1; j < BOARD_COL_SIZE - 1; j++){
			if (tetrisManager->board[i][j] != FIXED_BLOCK){
				tetrisManager->board[i][j] = EMPTY;
			}
		}
	}
	tetrisManager->board[0][0] = LEFT_TOP_EDGE;
	tetrisManager->board[0][BOARD_COL_SIZE - 1] = RIGHT_TOP_EDGE;
	tetrisManager->board[BOARD_ROW_SIZE - 1][0] = LEFT_BOTTOM_EDGE;
	tetrisManager->board[BOARD_ROW_SIZE - 1][BOARD_COL_SIZE - 1] = RIGHT_BOTTOM_EDGE;
}

static void _TetrisManager_ChangeBoardByStatus(TetrisManager* tetrisManager, int status){
	int i;
	for (i = 0; i < POSITIONS_SIZE; i++){
		int x = Block_GetPositions(tetrisManager->block)[i].x;
		int y = Block_GetPositions(tetrisManager->block)[i].y;
		tetrisManager->board[x][y] = status;
	}
}

static void _TetrisManager_UpSpeedLevel(TetrisManager* tetrisManager){
	if (tetrisManager->speedLevel < MAX_SPEED_LEVEL){
		tetrisManager->speedLevel++;
	}
}

static void _TetrisManager_SearchLineIndexesToDelete(TetrisManager* tetrisManager, int* indexes, int* count){
	int i;
	int j;
	int toDelete;
	memset(indexes, -1, sizeof(int)* (BOARD_ROW_SIZE - 2));
	*count = 0;
	for (i = 1; i < BOARD_ROW_SIZE - 1; i++){
		toDelete = True;
		for (j = 1; j < BOARD_COL_SIZE - 1; j++){
			if (tetrisManager->board[i][j] != FIXED_BLOCK){
				toDelete = False;
				break;
			}
		}
		if (toDelete){
			indexes[(*count)++] = i;
		}
	}
}

static void _TetrisManager_DeleteLines(TetrisManager* tetrisManager, int* indexes, int count){
	int i;
	int j;
	int k = BOARD_ROW_SIZE - 2;
	int toDelete;
	char temp[BOARD_ROW_SIZE][BOARD_COL_SIZE] = { EMPTY };
	for (i = BOARD_ROW_SIZE - 2; i > 0; i--){
		toDelete = False;
		for (j = 0; j < BOARD_COL_SIZE; j++){
			if (i == indexes[j]){
				toDelete = True;
				break;
			}
		}
		if (!toDelete){
			for (j = 0; j < BOARD_COL_SIZE; j++){
				temp[k][j] = tetrisManager->board[i][j];
			}
			k--;
		}
	}
	for (i = 1; i < BOARD_ROW_SIZE - 1; i++){
		for (j = 1; j < BOARD_COL_SIZE - 1; j++){
			tetrisManager->board[i][j] = temp[i][j];
		}
	}
	tetrisManager->deletedLineCount += count;
}