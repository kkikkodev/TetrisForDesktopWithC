#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "TetrisView.h"
#include "TetrisManager.h"
#include "Constant.h"
#include "Util.h"
#include "Menu.h"

#pragma comment(lib, "winmm.lib")

#define TETRIS_BACKGROUND_MUSIC_FILE_NAME "..\\res\\tetris_background_music.wav"

#define PROCESS_REACHED_CASE_COUNT 2

enum MenuStartPosition{
	MAIN_MENU_X = 18, MAIN_MENU_Y = 7, PAUSE_MENU_X = 5, PAUSE_MENU_Y = 12, END_MENU_X = 28, END_MENU_Y = 8
};

void TetrisView_StartGame(TetrisView* tetrisView){
	PlaySound(TEXT(TETRIS_BACKGROUND_MUSIC_FILE_NAME), NULL, SND_ASYNC | SND_LOOP);
	TetrisManager_Init(&tetrisView->tetrisManager, 1);
	system("cls");
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
		if (processType == DIRECT_DOWN){
			processReachedCaseCount = 0;
			if (TetrisManager_ProcessReachedCase(&tetrisView->tetrisManager) == END){
					TetrisView_EndGame(tetrisView);
					return;
			}
		}
		else{
			//if you are going to move the block which has bottom wall or bottom fixed block, permit the block to move the direction
			if (processReachedCaseCount == PROCESS_REACHED_CASE_COUNT){
				if (TetrisManager_ProcessReachedCase(&tetrisView->tetrisManager) == END){
					TetrisView_EndGame(tetrisView);
					return;
				}
				processReachedCaseCount = 0;
			}
			else{
				processReachedCaseCount++;
			}
		}
	}
	TetrisManager_Print(&tetrisView->tetrisManager);
	TetrisManager_ProcessDeletingLines(&tetrisView->tetrisManager);
}

void TetrisView_PauseGame(TetrisView* tetrisView){
	PlaySound(NULL, 0, 0);
	FontUtil_ChangeFontColor(LIGHT_YELLOW);
	TetrisView_ProcessPauseMenu(tetrisView);
	FontUtil_ChangeFontColor(WHITE);
	switch (tetrisView->pauseMenu){
	case RESUME_PAUSE_MENU:
		PlaySound(TEXT(TETRIS_BACKGROUND_MUSIC_FILE_NAME), NULL, SND_ASYNC | SND_LOOP);
		break;
	}
}

void TetrisView_EndGame(TetrisView* tetrisView){
	PlaySound(NULL, 0, 0);
	TetrisView_ProcessEndMenu(tetrisView);
}
DWORD TetrisView_GetDownMilliSecond(TetrisView* tetrisView){
	return TetrisManager_GetDownMilliSecond(&tetrisView->tetrisManager);
}

void TetrisView_ProcessMainMenu(TetrisView* tetrisView){
	Menu menu = { 0, };
	char items[MENU_ITEMS_COUNT][MENU_ITEMS_CONTENT_SIZE] = {
		"[1] S T A R T", "[2] R A N K I N G", "[3] S E T T I N G", "[4] E X I T"
	};
	int menuCount = 4;
	int x = MAIN_MENU_X;
	int y = MAIN_MENU_Y;
	system("cls");
	FontUtil_ChangeFontColor(RED);
	CursorUtil_GotoXY(x, y++);
	printf("бсбсбс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс");
	x += 8;
	y -= 5;
	FontUtil_ChangeFontColor(LIGHT_RED);
	CursorUtil_GotoXY(x, y++);
	printf("бсбсбс");
	CursorUtil_GotoXY(x, y++);
	printf("бс");
	CursorUtil_GotoXY(x, y++);
	printf("бсбсбс");
	CursorUtil_GotoXY(x, y++);
	printf("бс");
	CursorUtil_GotoXY(x, y++);
	printf("бсбсбс");
	x += 8;
	y -= 5;
	FontUtil_ChangeFontColor(LIGHT_YELLOW);
	CursorUtil_GotoXY(x, y++);
	printf("бсбсбс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс");
	x += 8;
	y -= 5;
	FontUtil_ChangeFontColor(GREEN);
	CursorUtil_GotoXY(x, y++);
	printf("бсбс");
	CursorUtil_GotoXY(x, y++);
	printf("бс бс");
	CursorUtil_GotoXY(x, y++);
	printf("бсбс");
	CursorUtil_GotoXY(x, y++);
	printf("бс бс");
	CursorUtil_GotoXY(x, y++);
	printf("бс  бс");
	x += 8;
	y -= 5;
	FontUtil_ChangeFontColor(LIGHT_BLUE);
	CursorUtil_GotoXY(x, y++);
	printf("бс");
	CursorUtil_GotoXY(x, y++);
	printf("бс");
	CursorUtil_GotoXY(x, y++);
	printf("бс");
	CursorUtil_GotoXY(x, y++);
	printf("бс");
	CursorUtil_GotoXY(x, y++);
	printf("бс");
	x += 4;
	y -= 5;
	FontUtil_ChangeFontColor(LIGHT_PURPLE);
	CursorUtil_GotoXY(x, y++);
	printf(" бсбс");
	CursorUtil_GotoXY(x, y++);
	printf("бс");
	CursorUtil_GotoXY(x, y++);
	printf("бсбсбс");
	CursorUtil_GotoXY(x, y++);
	printf("    бс");
	CursorUtil_GotoXY(x, y++);
	printf(" бсбс");
	x -= 22;
	y += 2;
	Menu_Create(&menu, items, menuCount, x, y);
	Menu_Print(&menu);
	tetrisView->mainMenu = Menu_ProcessKey(&menu) + 1;
	tetrisView->pauseMenu = 0;
	tetrisView->endMenu = 0;
}

void TetrisView_ProcessPauseMenu(TetrisView* tetrisView){
	Menu menu = { 0, };
	char items[MENU_ITEMS_COUNT][MENU_ITEMS_CONTENT_SIZE] = {
		"[1] R E S U M E", "[2] M A I N M E N U"
	};
	int menuCount = 2;
	int x = PAUSE_MENU_X;
	int y = PAUSE_MENU_Y;
	Menu_Create(&menu, items, menuCount, x, y);
	Menu_Print(&menu);
	tetrisView->pauseMenu = Menu_ProcessKey(&menu) + 1;
	tetrisView->mainMenu = 0;
	tetrisView->endMenu = 0;
}

void TetrisView_ProcessEndMenu(TetrisView* tetrisView){
	Menu menu = { 0, };
	char items[MENU_ITEMS_COUNT][MENU_ITEMS_CONTENT_SIZE] = {
		"[1] R A N K I N G", "[2] M A I N M E N U", "[3] E X I T"
	};
	int menuCount = 3;
	int x = END_MENU_X;
	int y = END_MENU_Y;
	system("cls");
	CursorUtil_GotoXY(x, y++);
	printf("бсбсбс          бсбсбс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс              бс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс              бс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс              бс");
	CursorUtil_GotoXY(x, y++);
	printf("  бс    бсбсбс    бс");
	x += 2;
	y += 2;
	Menu_Create(&menu, items, menuCount, x, y);
	Menu_Print(&menu);
	tetrisView->endMenu = Menu_ProcessKey(&menu) + 1;
	tetrisView->mainMenu = 0;
	tetrisView->pauseMenu = 0;
}
