#ifndef _BOARD_H
#define _BOARD_H

#include <windows.h>
#include "Block.h"

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
	int itemArray[7];
	int changeNextCount;		//레벨마다 다음블록과 다다음블록을 바꿀 수 있는 횟수를 지정

	HANDLE mutex;				//스레드에서 충돌을 피하기 위해 lock을 걸어준다.
	int checkBlindStatus;		/*다음블럭이 막혀있는 동안에는 다음블럭과 다다음블럭 바꾸기 기능을 할 수 없도록 제한하기 위해
								현재 블럭이 감추어져 있는 상태인지 아닌지를 체크한다.*/
	int blindNextInterval;		//레벨이 올라갈 때마다 다음블록을 감추는 주기를 짧게 설정한다.
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

void TetrisManager_AddItem(TetrisManager* tetrisManager); //아이템 추가 함수
void TetrisManager_UseItem(TetrisManager* tetrisManager, int index); //아이템 사용 함수

void TetrisManager_Item_RemoveOneRow(TetrisManager* tetrisManager);	//아이템1 : 한 줄 제거
void TetrisManager_Item_RemoveTwoRow(TetrisManager* tetrisManager);	//아이템2 : 두 줄 제거
void TetrisManager_Item_RemoveAllRow(TetrisManager* tetrisManager);	//아이템3 : 전체 줄 제거
void TetrisManager_ChangeNextBlock(TetrisManager* tetrisManager);	//다음블럭과 다다음블럭 바꾸기
void TetrisManager_BlindNextBlock(TetrisManager* tetrisManager);	//다음블럭 숨기기

void changeShadowColor(int level); // 레벨별로 그림자 색을 다르게 출력하는 함수

#endif