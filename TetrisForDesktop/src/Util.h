#ifndef _UTIL_H
#define _UTIL_H

#define FONT_COLOR_SIZE 16

enum FontColor{
	BLACK, BLUE, GREEN, JADE, RED, PURPLE, YELLOW, WHITE, GRAY,
	LIGHT_BLUE, LIGHT_GREEN, LIGHT_JADE, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE, WHITE_INVERSION = 240
};

void CursorUtil_GotoXY(int x, int y);
void CursorUtil_Hide();
void TimeUtil_Sleep(DWORD milliSecond);
void FontUtil_ChangeFontColor(int color);

#endif