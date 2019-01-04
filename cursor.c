#include <windows.h>

void cursor_getxy(int x, int y)
{
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hOut, &screen_buffer_info);
    x = screen_buffer_info.dwCursorPosition.X;
    y = screen_buffer_info.dwCursorPosition.Y;
}
void cursor_setxy(int x, int y)
{
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hOut, pos);
}
void cursor_enter()
{

}
