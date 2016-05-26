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
#define ADD_ID_POSITION_X_TO_PRINT 25
#define ADD_ID_POSITION_Y_TO_PRINT 10
#define SETTING_POSITION_X_TO_PRINT 30
#define SETTING_POSITION_Y_TO_PRINT 10

enum MenuStartPosition{
	MAIN_MENU_X = 18, MAIN_MENU_Y = 7, PAUSE_MENU_X = 5, PAUSE_MENU_Y = 12, END_MENU_X = 14, END_MENU_Y = 8
};

void TetrisView_StartGame(TetrisView* tetrisView){
	PlaySound(TEXT(TETRIS_BACKGROUND_MUSIC_FILE_NAME), NULL, SND_ASYNC | SND_LOOP); //배경음악 설정
	if (!(tetrisView->level >= MIN_SPEED_LEVEL && tetrisView->level <= MAX_SPEED_LEVEL)){ //현재 레벨이 MIN_SPEED_LEVEL(1)보다 크거나 같고 MAX_SPEED_LEVLE(10) 작거나 같지 않으면,
		tetrisView->level = MIN_SPEED_LEVEL; //1로 설정
	}
	TetrisManager_Init(&tetrisView->tetrisManager, tetrisView->level); //TetrisManager에서 Init 초기화 설정
	system("cls");
	FontUtil_ChangeFontColor(DEFAULT_FONT_COLOR);  //기본 Font 색상으로 설정
	TetrisManager_PrintBoard(&tetrisView->tetrisManager); //게임창 출력
	TetrisManager_PrintDetailInfomation(&tetrisView->tetrisManager); // 게임의 모든 정보를 출력
}

void TetrisView_ProcessGame(TetrisView* tetrisView, int processType, int direction){
	//게임이 진행 되면서 설정되는 ProcessType 별 실행과정
	//it is used to move left or right at bottom in case of space which you want to move is available
	static int processReachedCaseCount = 0;
	if (processType == DIRECTION){ //방향키를 넣었을 경우
		TetrisManager_ProcessDirection(&tetrisView->tetrisManager, direction);
	}
	else if (processType == DIRECT_DOWN){
		TetrisManager_ProcessDirectDown(&tetrisView->tetrisManager); //스페이스바를 입력했을 경우
	}
	else if (processType == AUTO){ //자동으로 블록이 떨어지는 것을 의미
		TetrisManager_ProcessAuto(&tetrisView->tetrisManager);
	}
	if (TetrisManager_IsReachedToBottom(&tetrisView->tetrisManager, MOVING_BLOCK)){ //블록이 바닥에 닿았을 경우
		if (processType == DIRECT_DOWN){ //스페이스바 입력이라면
			processReachedCaseCount = 0;
			if (TetrisManager_ProcessReachedCase(&tetrisView->tetrisManager) == END){
				TetrisView_EndGame(tetrisView); //가장 위에 블록이 모두 쌓였을 때, 게임 중지와 함께 종료 화면
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
	TetrisManager_ProcessDeletingLines(&tetrisView->tetrisManager); //굳어진 블록이 한줄을 이루었을 경우, 한줄 삭제
}

void TetrisView_PauseGame(TetrisView* tetrisView){
	TetrisManager_PauseTotalTime(&tetrisView->tetrisManager); //게임 진행 시간 중지
	PlaySound(NULL, 0, 0); //배경음악 중단
	FontUtil_ChangeFontColor(LIGHT_YELLOW); //메뉴 색상 노랑색으로 변경
	TetrisView_ProcessPauseMenu(tetrisView); //중지되었을 때, 메뉴 화면 출력
	FontUtil_ChangeFontColor(DEFAULT_FONT_COLOR);
	switch (tetrisView->pauseMenu){
	case RESUME_PAUSE_MENU: //재시작
		TetrisManager_StartTotalTime(&tetrisView->tetrisManager);
		PlaySound(TEXT(TETRIS_BACKGROUND_MUSIC_FILE_NAME), NULL, SND_ASYNC | SND_LOOP);
		break;
	case MAIN_MENU_PAUSE_MENU://메인화면으로 이동
		TetrisManager_StopTotalTime(&tetrisView->tetrisManager);
		break;
	}
}

void TetrisView_EndGame(TetrisView* tetrisView){
	TetrisManager_PauseTotalTime(&tetrisView->tetrisManager);
	PlaySound(NULL, 0, 0);
	TetrisView_ProcessEndMenu(tetrisView);
}

void TetrisView_ShowRanking(TetrisView* tetrisView){
	RankingManager_Create(&tetrisView->rankingManager);
	RankingManager_Load(&tetrisView->rankingManager);
	RankingManager_Print(&tetrisView->rankingManager);
	RankingManager_Destroy(&tetrisView->rankingManager);
}

void TetrisView_AddRanking(TetrisView* tetrisView){
	Ranking ranking;
	int x = ADD_ID_POSITION_X_TO_PRINT;
	int y = ADD_ID_POSITION_Y_TO_PRINT;
	int i;
	char id[ID_SIZE + 1] = { '\0', };
	system("cls");
	CursorUtil_GotoXY(x, y++); //아이디 입력창 출력
	printf("┏━━━━━━━━━━━━━┓");
	CursorUtil_GotoXY(x, y++);
	printf("┃Input ID (%d chars limit!)┃", ID_SIZE);
	CursorUtil_GotoXY(x, y++);
	printf("┃:                         ┃");
	CursorUtil_GotoXY(x, y++);
	printf("┗━━━━━━━━━━━━━┛");
	x += 4;
	y -= 2;
	CursorUtil_GotoXY(x, y++);
	CursorUtil_Show();
	fgets(id, ID_SIZE + 1, stdin);
	CursorUtil_Hide();
	for (i = ID_SIZE; i >= 0; i--){
		if (id[i] == '\n'){
			id[i] = '\0';
			break;
		}
	}
	if (i == -1){
		while (getchar() != '\n');
	}
	strcpy(ranking.id, id); // 입력받은 아이디 저장
	ranking.score = tetrisView->tetrisManager.score; //현재 점수
	ranking.level = tetrisView->tetrisManager.speedLevel; // 현재 레벨
	ranking.deletedLineCount = tetrisView->tetrisManager.deletedLineCount; //현재 삭제 라인 수
	ranking.totalTime = tetrisView->tetrisManager.totalTime; // 게임 진행 총 시간
	ranking.timestamp = time(NULL); 
	//Ranking 등록에 필요한 모든 작업
	RankingManager_Create(&tetrisView->rankingManager); 
	RankingManager_Load(&tetrisView->rankingManager);
	RankingManager_Add(&tetrisView->rankingManager, ranking);
	RankingManager_Save(&tetrisView->rankingManager);
	RankingManager_Destroy(&tetrisView->rankingManager);
}

void TetrisView_ShowSetting(TetrisView* tetrisView){
	int x = SETTING_POSITION_X_TO_PRINT;
	int y = SETTING_POSITION_Y_TO_PRINT;
	if (!(tetrisView->level >= MIN_SPEED_LEVEL && tetrisView->level <= MAX_SPEED_LEVEL)){
		tetrisView->level = MIN_SPEED_LEVEL;
	}
	system("cls");
	CursorUtil_GotoXY(x, y++); //레벨 입력창
	printf("┏━━━━━━━━━┓");
	CursorUtil_GotoXY(x, y++);
	printf("┃Current Level : %2d┃", tetrisView->level);
	CursorUtil_GotoXY(x, y++);
	printf("┃New Level (%d ~ %d)┃", MIN_SPEED_LEVEL, MAX_SPEED_LEVEL);
	CursorUtil_GotoXY(x, y++);
	printf("┃:                 ┃");
	CursorUtil_GotoXY(x, y++);
	printf("┗━━━━━━━━━┛");
	x += 4;
	y -= 2;
	CursorUtil_GotoXY(x, y++);
	CursorUtil_Show();
	scanf("%d", &tetrisView->level);
	CursorUtil_Hide();
	if (tetrisView->level >= MIN_SPEED_LEVEL && tetrisView->level <= MAX_SPEED_LEVEL){

	}
	else if (tetrisView->level < MIN_SPEED_LEVEL){ //입력된 레벨이 최소값보다 작을 경우 
		tetrisView->level = MIN_SPEED_LEVEL;
	}
	else if (tetrisView->level > MAX_SPEED_LEVEL){ //입력된 레벨이 최대값보다 클경우
		tetrisView->level = MAX_SPEED_LEVEL;
	}
	else{
		tetrisView->level = MIN_SPEED_LEVEL;
	}
	while (getchar() != '\n');
}

void TetrisView_ProcessMainMenu(TetrisView* tetrisView){
	Menu menu = { 0, };
	char items[MENU_ITEMS_COUNT][MENU_ITEMS_CONTENT_SIZE] = {
		"[1] S T A R T", "[2] R A N K I N G", "[3] S E T T I N G", "[4] E X I T"
	};
	int menuCount = 4;
	int x = MAIN_MENU_X;
	int y = MAIN_MENU_Y;
	WindowUtil_ChangeWindowSize(WINDOW_LINE_SIZE, WINDOW_COL_SIZE);
	system("cls");
	FontUtil_ChangeFontColor(RED);
	CursorUtil_GotoXY(x, y++);
	printf("■■■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■");
	x += 8;
	y -= 5;
	FontUtil_ChangeFontColor(LIGHT_RED);
	CursorUtil_GotoXY(x, y++);
	printf("■■■");
	CursorUtil_GotoXY(x, y++);
	printf("■");
	CursorUtil_GotoXY(x, y++);
	printf("■■■");
	CursorUtil_GotoXY(x, y++);
	printf("■");
	CursorUtil_GotoXY(x, y++);
	printf("■■■");
	x += 8;
	y -= 5;
	FontUtil_ChangeFontColor(LIGHT_YELLOW);
	CursorUtil_GotoXY(x, y++);
	printf("■■■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■");
	x += 8;
	y -= 5;
	FontUtil_ChangeFontColor(GREEN);
	CursorUtil_GotoXY(x, y++);
	printf("■■");
	CursorUtil_GotoXY(x, y++);
	printf("■ ■");
	CursorUtil_GotoXY(x, y++);
	printf("■■");
	CursorUtil_GotoXY(x, y++);
	printf("■ ■");
	CursorUtil_GotoXY(x, y++);
	printf("■  ■");
	x += 8;
	y -= 5;
	FontUtil_ChangeFontColor(LIGHT_BLUE);
	CursorUtil_GotoXY(x, y++);
	printf("■");
	CursorUtil_GotoXY(x, y++);
	printf("■");
	CursorUtil_GotoXY(x, y++);
	printf("■");
	CursorUtil_GotoXY(x, y++);
	printf("■");
	CursorUtil_GotoXY(x, y++);
	printf("■");
	x += 4;
	y -= 5;
	FontUtil_ChangeFontColor(LIGHT_PURPLE);
	CursorUtil_GotoXY(x, y++);
	printf(" ■■");
	CursorUtil_GotoXY(x, y++);
	printf("■");
	CursorUtil_GotoXY(x, y++);
	printf("■■■");
	CursorUtil_GotoXY(x, y++);
	printf("    ■");
	CursorUtil_GotoXY(x, y++);
	printf(" ■■");
	x -= 22;
	y += 2;
	Menu_Create(&menu, items, menuCount, x, y, DEFAULT_FONT_COLOR);
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
	Menu_Create(&menu, items, menuCount, x, y, LIGHT_YELLOW);
	Menu_Print(&menu);
	tetrisView->pauseMenu = Menu_ProcessKey(&menu) + 1;
	tetrisView->mainMenu = 0;
	tetrisView->endMenu = 0;
	if (tetrisView->pauseMenu == RESUME_PAUSE_MENU){
		TetrisManager_PrintBoard(&tetrisView->tetrisManager);
	}
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
	printf("■■■  ■  ■  ■■■          ■■■  ■  ■  ■■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■    ■  ■  ■              ■       ■ ■  ■ ■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■    ■■■  ■■■  ■■■  ■■■  ■■■  ■  ■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■    ■  ■  ■              ■      ■ ■   ■ ■");
	CursorUtil_GotoXY(x, y++);
	printf("  ■    ■  ■  ■■■          ■■■  ■  ■  ■■");
	x += 19;
	y += 2;
	Menu_Create(&menu, items, menuCount, x, y, DEFAULT_FONT_COLOR);
	Menu_Print(&menu);
	tetrisView->endMenu = Menu_ProcessKey(&menu) + 1;
	tetrisView->mainMenu = 0;
	tetrisView->pauseMenu = 0;
}

DWORD TetrisView_GetDownMilliSecond(TetrisView* tetrisView){
	return TetrisManager_GetDownMilliSecond(&tetrisView->tetrisManager);
}

void TetrisView_MakeHold(TetrisView* tetrisView){
	TetrisManager_MakeHold(&tetrisView->tetrisManager);
}