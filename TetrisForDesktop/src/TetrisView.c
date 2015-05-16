#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "TetrisView.h"
#include "TetrisManager.h"
#include "Constant.h"
#include "Util.h"

#pragma comment(lib, "winmm.lib")

#define TETRIS_BACKGROUND_MUSIC_FILE_NAME "..\\res\\tetris_background_music.wav"

#define PROCESS_REACHED_CASE_COUNT 2

void TetrisView_StartGame(TetrisView* tetrisView){
	int speedLevel;
	PlaySound(TEXT(TETRIS_BACKGROUND_MUSIC_FILE_NAME), NULL, SND_ASYNC | SND_LOOP);
	printf("***** Tetris *****\nSpeed level (1 ~ 10) : ");
	scanf_s("%d", &speedLevel);
	if (speedLevel > MAX_SPEED_LEVEL || speedLevel < MIN_SPEED_LEVEL){
		speedLevel = MIN_SPEED_LEVEL;
	}
	TetrisManager_Init(&tetrisView->tetrisManager, speedLevel);
	TetrisManager_Print(&tetrisView->tetrisManager);
}

void TetrisView_ProcessGame(TetrisView* tetrisView, int processType, int direction){

	//it is used to move left or right at bottom in case of space which you want to move is available
	static int processReachedCaseCount = 0;
	if (processType == DIRECTION){
		TetrisManager_ChangeBoardByDirection(&tetrisView->tetrisManager, direction);
	}
	else if (processType == DIRECT_DOWN){
		TetrisManager_ProcessDirectDown(&tetrisView->tetrisManager);
	}
	else if (processType == AUTO){
		TetrisManager_ChangeBoardByAuto(&tetrisView->tetrisManager);
	}
	if (TetrisManager_IsReachedToBottom(&tetrisView->tetrisManager)){
		//if you are going to move the block which has bottom wall or bottom fixed block, permit the block to move the direction
		if (processReachedCaseCount == PROCESS_REACHED_CASE_COUNT){
			if (TetrisManager_ProcessReachedCase(&tetrisView->tetrisManager) == END){
				TetrisView_EndGame(tetrisView);
			}
			processReachedCaseCount = 0;
		}
		else{
			processReachedCaseCount++;
		}
	}
	TetrisManager_Print(&tetrisView->tetrisManager);
	TetrisManager_ProcessDeletingLines(&tetrisView->tetrisManager);
}

void TetrisView_EndGame(TetrisView* tetrisView){
	PlaySound(NULL, 0, 0);
	system("cls");
	printf("***** End *****\n%d level / %d lines deleted\n",
		tetrisView->tetrisManager.speedLevel,
		tetrisView->tetrisManager.deletedLineCount);
	system("pause");
	exit(-1);
}

void TetrisView_PauseGame(TetrisView* tetrisView){
	PlaySound(NULL, 0, 0);
	FontUtil_ChangeFontColor(LIGHT_YELLOW);
	CursorUtil_GotoXY(BOARD_ROW_SIZE / 2 + 1, BOARD_COL_SIZE / 2 + 1);
	printf("[pause]");
	CursorUtil_GotoXY(BOARD_ROW_SIZE / 2 - 2, BOARD_COL_SIZE / 2 + 2);
	printf("press any key");
	CursorUtil_GotoXY(BOARD_ROW_SIZE / 2 - 1, BOARD_COL_SIZE / 2 + 3);
	printf("to continue");
	FontUtil_ChangeFontColor(WHITE);
	system("pause > nul");
	PlaySound(TEXT(TETRIS_BACKGROUND_MUSIC_FILE_NAME), NULL, SND_ASYNC | SND_LOOP);
}

DWORD TetrisView_GetDownMilliSecond(TetrisView* tetrisView){
	return TetrisManager_GetDownMilliSecond(&tetrisView->tetrisManager);
}