#ifndef _BOARD_H
#define _BOARD_H

#include "Block.h"

enum GameStatus{
	PLAYING, END
};

#define BOARD_ROW_SIZE 20
#define BOARD_COL_SIZE 14

typedef struct _tetrisManager{
	char board[BOARD_ROW_SIZE][BOARD_COL_SIZE];
	Block block;
	int deletedLineCount;
	int speedLevel;
}TetrisManager;

void TetrisManager_Init(TetrisManager* tetrisManager, int speedLevel); 
int TetrisManager_CheckValidPosition(TetrisManager* tetrisManager, int direction);
void TetrisManager_ChangeBoardByDirection(TetrisManager* tetrisManager, int direction);
void TetrisManager_ChangeBoardByAuto(TetrisManager* tetrisManager);
void TetrisManager_ProcessDirectDown(TetrisManager* tetrisManager);
void TetrisManager_ProcessDeletingLines(TetrisManager* tetrisManager);
int TetrisManager_IsReachedToBottom(TetrisManager* tetrisManager);
int TetrisManager_ProcessReachedCase(TetrisManager* tetrisManager);
void TetrisManager_Sleep(TetrisManager* tetrisManager);
void TetrisManager_Print(TetrisManager* tetrisManager);

#endif