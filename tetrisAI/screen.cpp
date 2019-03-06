#include "screen.h"

CScreen::CScreen()
{
	consoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
}
CScreen::~CScreen()
{
}
void CScreen::setCursorPosition(short x, short y)
{
	COORD position={x, y};
	
	SetConsoleCursorPosition(consoleOutput, position);
}
void CScreen::setTextAttribute(unsigned short attribute)
{
	SetConsoleTextAttribute(consoleOutput, attribute);
}
void CScreen::showCursor(bool visible)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	
	cursorInfo.bVisible=visible;
	cursorInfo.dwSize=10;
	
	SetConsoleCursorInfo(consoleOutput, &cursorInfo);
}