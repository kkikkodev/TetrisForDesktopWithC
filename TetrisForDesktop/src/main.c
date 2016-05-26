#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Constant.h"
#include "TetrisView.h"
#include "TetrisManager.h"

int main(int argc, char* argv[]){
	TetrisView tetrisView;
	int processType;
	int direction;
	DWORD tickCount;
	int isSetMainMenu = False;
	do{
		TetrisView_ProcessMainMenu(&tetrisView);
		switch (tetrisView.mainMenu){
		case START_MAIN_MENU:
			TetrisView_StartGame(&tetrisView); //게임 시작 화면
			tickCount = GetTickCount();
			while (True){
				processType = AUTO; 
				direction = DOWN; // processType과 direction을 설정하여 자동으로 아래방향으로 블록이 내려오도록 함
				isSetMainMenu = False; //게임 플레이 화면으로 이동
				while (True){
					if (GetTickCount() - tickCount > TetrisView_GetDownMilliSecond(&tetrisView)){ //블럭 내려오는 딜레이 방식을 프레임 단위로 쪼개는 방식으로 변경
						processType = AUTO;
						direction = DOWN;
						tickCount = GetTickCount();
						break;
					}
					if (_kbhit()){
						int key = _getch();
						if (key == 0xE0 && _kbhit()){ // 키값이 224이거나 비동기적으로 체크하여 입력 버퍼 값이 정수로 입력됨을 확인
							key = _getch();
							if (key == UP_KEY_CODE){ //Constant.h에 저장되어 있는 값을 입력받음
								processType = DIRECTION; //그에 맞게 방향과 타입을 설정
								direction = UP;
								break;
							}
							if (key == DOWN_KEY_CODE){
								processType = DIRECTION;
								direction = DOWN;
								tickCount = GetTickCount();
								break;
							}
							if (key == LEFT_KEY_CODE){
								processType = DIRECTION;
								direction = LEFT;
								break;
							}
							if (key == RIGHT_KEY_CODE){
								processType = DIRECTION;
								direction = RIGHT;
								break;
							}
						}
						else{
							if (key == SPACE_BAR_KEY_CODE){ //스페이스바를 입력했을 경우
								processType = DIRECT_DOWN; //곧장 아래방향으로 내려가는 명령
								tickCount = GetTickCount();
								break;
							}
							if (key == ESC_KEY_CODE){ //ESC키를 입력했을 경우
								TetrisView_PauseGame(&tetrisView); //정지화면 출력
								if (tetrisView.pauseMenu == MAIN_MENU_PAUSE_MENU){ //Main Menu로 돌아가기 선택시
									isSetMainMenu = True; 
									break;
								}
								processType = AUTO; //자동으로 변경
								tickCount = GetTickCount();
								break;
							}
							if (key == L_KEY_CODE){ //현재 블록을 홀드 할수 있는 키
								TetrisView_MakeHold(&tetrisView);
							}
						}
						if (key == ITEM_FIRST_CODE){  //첫번째 아이템 사용 Z
							TetrisManager_UseItem(&tetrisView.tetrisManager, 1);
							break;
						}
						if (key == ITEM_SECOND_CODE){ //두번째 아이템 사용 X
							TetrisManager_UseItem(&tetrisView.tetrisManager, 2);
							break;
						}
						if (key == ITEM_THRID_CODE){  //세번째 아이템 사용 X
							TetrisManager_UseItem(&tetrisView.tetrisManager, 3);
							break;
						}
						if (key == ITEM_FOURTH_CODE){ //네번째 아이템 사용 V
							TetrisManager_UseItem(&tetrisView.tetrisManager, 4);
							break;
						}
					}
				}

				//for selecting main menu at pause menu
				if (isSetMainMenu){
					break;
				}//게임이 중단 되었을 경우 
				TetrisView_ProcessGame(&tetrisView, processType, direction);
				if (tetrisView.endMenu == RANKING_END_MENU){ 
					TetrisView_AddRanking(&tetrisView); //Rank 등록
					TetrisView_ShowRanking(&tetrisView); //전체 Ranking 조회
					break;
				}
				else if (tetrisView.endMenu == MAIN_MENU_END_MENU){ //게임이 전체 종료 되어지면서 Main Menu로 이동하게 됨
					break;
				}
				else if (tetrisView.endMenu == EXIT_END_MENU){ //프로그램 종료
					tetrisView.mainMenu = EXIT_MAIN_MENU;
					break;
				}
			}
			break;
		case RANKING_MAIN_MENU: // Main Menu에서 Ranking 화면으로 이동
			TetrisView_ShowRanking(&tetrisView);
			break;
		case SETTING_MAIN_MENU: // Main Menu Setting화면으로 이동
			TetrisView_ShowSetting(&tetrisView);
			break;
		}
	} while (tetrisView.mainMenu != EXIT_MAIN_MENU); // Main Menu에서 프로그램 종료
	return 0;
}