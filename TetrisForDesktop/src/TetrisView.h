#ifndef _TETRIS_VIEW_H
#define _TETRIS_VIEW_H

#include "TetrisManager.h"

typedef struct _tetrisView{
	TetrisManager tetrisManager;
}TetrisView;

void TetrisView_StartGame(TetrisView* tetrisView);
void TetrisView_ProcessGame(TetrisView* tetrisView, int processType, int direction);
void TetrisView_EndGame(TetrisView* tetrisView);
DWORD TetrisView_GetDownMilliSecond(TetrisView* tetrisView); //make temporarily for calling from main function

#endif