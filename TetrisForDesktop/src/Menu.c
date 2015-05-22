#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Menu.h"
#include "Util.h"

enum KeyCode{
	ENTER = 13, UP = 72, DOWN = 80
};

enum Boolean{
	False, True
};

void Menu_Create(Menu* menu, char(*items)[MENU_ITEMS_CONTENT_SIZE], int count, int startPositionXToPrint, int startPositionYToPrint){
	int i;
	for (i = 0; i < count; i++){
		strcpy(menu->items[i], items[i]);
	}
	menu->count = count;
	menu->selectedIndex = 0;
	menu->startPositionToPrint.x = startPositionXToPrint;
	menu->startPositionToPrint.y = startPositionYToPrint;
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
			FontUtil_ChangeFontColor(WHITE);
		}
		printf("%s", menu->items[i]);
	}
	FontUtil_ChangeFontColor(WHITE);
}

int Menu_ProcessKey(Menu* menu){
	while (True){
		if (_kbhit()){
			int key = _getch();
			if (key == ENTER){
				break;
			}
			switch (key){
			case 0xE0:
				if (_kbhit()){
					switch (_getch()){
					case UP:
						menu->selectedIndex = (menu->selectedIndex - 1 + menu->count) % menu->count;
						Menu_Print(menu);
						break;
					case DOWN:
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
