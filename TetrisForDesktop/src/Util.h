#ifndef _UTIL_H
#define _UTIL_H

#define FONT_COLOR_SIZE 16
#define WINDOW_LINE_SIZE 25
#define WINDOW_COL_SIZE 80

void CursorUtil_GotoXY(int x, int y);
void CursorUtil_Show();
void CursorUtil_Hide();
void WindowUtil_ChangeWindowSize(int lines, int cols);
void FontUtil_ChangeFontColor(int color);
void ScreenUtil_ClearRectangle(int leftTopX, int leftTopY, int width, int height);

#endif