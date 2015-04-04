#include <stdio.h>
#include <conio.h>
#include "Constant.h"
#include "TetrisView.h"

int main(int argc, char* argv[]){
	TetrisView tetrisView;
	TetrisView_StartGame(&tetrisView);
	int processType;
	int direction;
	while (True){
		processType = AUTO;
		direction = DOWN;
		if (_kbhit()){
			int key = _getch();
			if (_kbhit()){
				key = _getch();
				switch (key){
				case UP_KEY_CODE:
					processType = DIRECTION;
					direction = UP;
					break;
				case LEFT_KEY_CODE:
					processType = DIRECTION;
					direction = LEFT;
					break;
				case RIGHT_KEY_CODE:
					processType = DIRECTION;
					direction = RIGHT;
					break;
				case DOWN_KEY_CODE:
					processType = DIRECTION;
					direction = DOWN;
					break;
				}
			}
			else{
				switch (key){
				case SPACE_BAR_KEY_CODE:
					processType = DIRECT_DOWN;
				}
			}
		}
		TetrisView_ProcessGame(&tetrisView, processType, direction);
	}
	return 0;
}