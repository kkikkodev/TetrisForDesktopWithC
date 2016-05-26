#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Menu.h"
#include "Util.h"
#include "Constant.h"

void Menu_Create(Menu* menu, char(*items)[MENU_ITEMS_CONTENT_SIZE], int count, int startPositionXToPrint, int startPositionYToPrint, int menuColor){
	int i;
	for (i = 0; i < count; i++){
		strcpy(menu->items[i], items[i]);
	}
	menu->count = count;
	menu->selectedIndex = 0;
	menu->startPositionToPrint.x = startPositionXToPrint;
	menu->startPositionToPrint.y = startPositionYToPrint;
	menu->menuColor = menuColor;
}

void Menu_Print(Menu* menu){
	int i;
	int startPositionXToPrint = menu->startPositionToPrint.x;
	int startPositionYToPrint = menu->startPositionToPrint.y;
	CursorUtil_Hide();
	for (i = 0; i < menu->count; i++){
		CursorUtil_GotoXY(startPositionXToPrint, startPositionYToPrint++);
		if (i == menu->selectedIndex){
			FontUtil_ChangeFontColor(WHITE_INVERSION);
		}
		else{
			FontUtil_ChangeFontColor(menu->menuColor);
		}
		printf("%s", menu->items[i]);
	}
	FontUtil_ChangeFontColor(DEFAULT_FONT_COLOR);
}

int Menu_ProcessKey(Menu* menu){
	while (True){
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

const char* Menu_GetSelectedContent(Menu* menu){
	return menu->items[menu->selectedIndex];
}
