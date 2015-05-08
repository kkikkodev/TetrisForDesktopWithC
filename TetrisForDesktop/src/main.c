#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "Constant.h"
#include "TetrisView.h"

int main(int argc, char* argv[]){
	TetrisView tetrisView;
	TetrisView_StartGame(&tetrisView);
	int processType;
	int direction;
	DWORD tickCount = GetTickCount();
	while (True){
		processType = AUTO;
		direction = DOWN;
		while (True){
			if (GetTickCount() - tickCount > TetrisView_GetDownMilliSecond(&tetrisView)){
				processType = AUTO;
				direction = DOWN;
				tickCount = GetTickCount();
				break;
			}
			if (_kbhit()){
				int key = _getch();
				if (_kbhit()){
					key = _getch();
					if (key == UP_KEY_CODE){
						processType = DIRECTION;
						direction = UP;
						break;
					}
					else if (key == DOWN_KEY_CODE){
						processType = DIRECTION;
						direction = DOWN;
						tickCount = GetTickCount();
						break;
					}
					else if (key == LEFT_KEY_CODE){
						processType = DIRECTION;
						direction = LEFT;
						break;
					}
					else if (key == RIGHT_KEY_CODE){
						processType = DIRECTION;
						direction = RIGHT;
						break;
					}
				}
				else{
					if (key == SPACE_BAR_KEY_CODE){
						processType = DIRECT_DOWN;
						tickCount = GetTickCount();
						break;
					}
				}
			}
		}
		TetrisView_ProcessGame(&tetrisView, processType, direction);
	}
	return 0;
}