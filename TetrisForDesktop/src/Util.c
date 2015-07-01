#include <windows.h>
#include <stdio.h>
#include "Util.h"

#define COMMAND_SIZE 256
#define CURSOR_SIZE 30

void CursorUtil_GotoXY(int x, int y){
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorUtil_Show(){
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = TRUE;
	cursorInfo.dwSize = CURSOR_SIZE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void CursorUtil_Hide(){
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void WindowUtil_ChangeWindowSize(int lines, int cols){
	char command[COMMAND_SIZE] = { '\0', };
	sprintf(command, "mode con: lines=%d cols=%d", lines, cols);
	system(command);
}

void FontUtil_ChangeFontColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ScreenUtil_ClearRectangle(int leftTopX, int leftTopY, int width, int height){
	int i;
	int j;
	CursorUtil_GotoXY(leftTopX, leftTopY++);
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			printf(" ");
		}
		CursorUtil_GotoXY(leftTopX, leftTopY++);
	}
}