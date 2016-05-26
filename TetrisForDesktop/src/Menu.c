#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Menu.h"
#include "Util.h"
#include "Constant.h"

void Menu_Create(Menu* menu, char(*items)[MENU_ITEMS_CONTENT_SIZE], int count, int startPositionXToPrint, int startPositionYToPrint, int menuColor){
	//메뉴 생성
	int i;
	for (i = 0; i < count; i++){
		strcpy(menu->items[i], items[i]); //메뉴 Title 저장
	}
	menu->count = count; //Menu의 총 갯수
	menu->selectedIndex = 0; //선택된 메뉴의 Index
	menu->startPositionToPrint.x = startPositionXToPrint; //메뉴가 위치할 곳
	menu->startPositionToPrint.y = startPositionYToPrint;
	menu->menuColor = menuColor; //Text Color지정
}

void Menu_Print(Menu* menu){ //View 적인 면
	int i;
	int startPositionXToPrint = menu->startPositionToPrint.x;
	int startPositionYToPrint = menu->startPositionToPrint.y;
	CursorUtil_Hide();
	for (i = 0; i < menu->count; i++){
		CursorUtil_GotoXY(startPositionXToPrint, startPositionYToPrint++);
		if (i == menu->selectedIndex){
			FontUtil_ChangeFontColor(WHITE_INVERSION); // 선택된 값은 반전된 색으로 변경
		}
		else{
			FontUtil_ChangeFontColor(menu->menuColor); // 선택되지 않았다면 원래 색을 유지
		}
		printf("%s", menu->items[i]);
	}
	FontUtil_ChangeFontColor(DEFAULT_FONT_COLOR);
}

int Menu_ProcessKey(Menu* menu){
	while (True){ //UP키와 DOWN 키로 메뉴를 고르고 Enter키를 통해 입력 값이 리턴
		if (_kbhit()){
			int key = _getch();
			if (key == ENTER_KEY_CODE){
				break;
			}
			switch (key){
			case 0xE0:
				if (_kbhit()){
					switch (_getch()){
					case UP_KEY_CODE:
						menu->selectedIndex = (menu->selectedIndex - 1 + menu->count) % menu->count;
						Menu_Print(menu);
						break;
					case DOWN_KEY_CODE:
						menu->selectedIndex = (menu->selectedIndex + 1) % menu->count; 
						Menu_Print(menu);
						break;
					}
				}
				break;
			}
		}
	}
	return menu->selectedIndex;
}

const char* Menu_GetSelectedContent(Menu* menu){ //Menu 선택값을 리턴
	return menu->items[menu->selectedIndex];
}
