#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "TetrisView.h"
#include "TetrisManager.h"
#include "Constant.h"

#pragma comment(lib, "winmm.lib")

#define TETRIS_BACKGROUND_MUSIC_FILE_NAME "..\\res\\tetris_background_music.wav"

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
		if (processType == DIRECTION && direction == LEFT && (TetrisManager_CheckValidPosition(&tetrisView->tetrisManager, LEFT) == EMPTY) || 
			processType == DIRECTION && direction == RIGHT && (TetrisManager_CheckValidPosition(&tetrisView->tetrisManager, RIGHT) == EMPTY)){
			TetrisManager_ChangeBoardByDirection(&tetrisView->tetrisManager, direction);
		}
		if (TetrisManager_ProcessReachedCase(&tetrisView->tetrisManager) == END){
			TetrisView_EndGame(tetrisView);
		}
	}
	TetrisManager_ProcessDeletingLines(&tetrisView->tetrisManager);
	TetrisManager_Print(&tetrisView->tetrisManager);
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

DWORD TetrisView_GetDownMilliSecond(TetrisView* tetrisView){
	return TetrisManager_GetDownMilliSecond(&tetrisView->tetrisManager);
}