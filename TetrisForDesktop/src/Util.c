#include <windows.h>
#include <stdio.h>
#include "Util.h"

#define COMMAND_SIZE 256

void CursorUtil_GotoXY(int x, int y){
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorUtil_Hide(){
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
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