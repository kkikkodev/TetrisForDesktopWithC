#ifndef _BOARD_H
#define _BOARD_H

#include <windows.h>
#include "Block.h"
#include "Time.h"

enum GameStatus{
	PLAYING, END
};

#define BOARD_ROW_SIZE 24
#define BOARD_COL_SIZE 14

typedef struct _tetrisManager{
	char board[BOARD_ROW_SIZE][BOARD_COL_SIZE];
	Block block;
	int isHoldAvailable; // if hold block is empty or hold turn is passed, this variable is true
	Block shadow;
	int deletedLineCount;
	int speedLevel;
	int score;
	HANDLE totalTimeThread;
	long totalTime;
	int isTotalTimeAvailable; // if totalTimeThread is alive, this variable is true
	int currentDeleteLineCount; //현재 지운 라인의 수
	int maxCombo; //최대 콤보 수
	int isCombo; //콤보의 여부
	int currentCombo; //현재 콤보 수
	time_t currentDeleteTime; //현재 라인 삭제 시간
	time_t lastDeleteTime; //마지막 라인 삭제 시간
	time_t diffTime; //라인 삭제 시간차
	int item_o_flag; //Item check
	int item_cnt; //Item check
	

}TetrisManager;

void TetrisManager_Init(TetrisManager* tetrisManager, int speedLevel);
void TetrisManager_ProcessDirection(TetrisManager* tetrisManager, int direction);
void TetrisManager_ProcessAuto(TetrisManager* tetrisManager);
void TetrisManager_ProcessDirectDown(TetrisManager* tetrisManager);
void TetrisManager_ProcessDeletingLines(TetrisManager* tetrisManager);
int TetrisManager_IsReachedToBottom(TetrisManager* tetrisManager, int blockType);
int TetrisManager_ProcessReachedCase(TetrisManager* tetrisManager);
void TetrisManager_Print(TetrisManager* tetrisManager);
void TetrisManager_PrintBoard(TetrisManager* tetrisManager);
void TetrisManager_PrintDetailInfomation(TetrisManager* tetrisManager);
DWORD TetrisManager_GetDownMilliSecond(TetrisManager* tetrisManager);
void TetrisManager_MakeHold(TetrisManager* tetrisManager);
void TetrisManager_StartTotalTime(TetrisManager* tetrisManager);
void TetrisManager_PauseTotalTime(TetrisManager* tetrisManager);
void TetrisManager_StopTotalTime(TetrisManager* tetrisManager);
void TetrisManager_MakeItem(TetrisManager* tetrisManager); //Level 3,6,9 Item 함

#endif
