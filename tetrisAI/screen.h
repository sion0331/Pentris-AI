#pragma once

#include <windows.h>

class CScreen
{
private:
	HANDLE consoleOutput;
	
public:
	CScreen();
	virtual ~CScreen();
	
	void setCursorPosition(short x, short y);
	void setTextAttribute(unsigned short attribute);
	void showCursor(bool visible=true);
};