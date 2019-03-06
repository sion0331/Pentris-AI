#pragma once

#include <stdio.h>
#include "screen.h"

enum _tagTILE
{
	_EMPTY,
	_UNSUREBRICK,
	_BRICK,
	_WALL,
	_NONE
};
typedef enum _tagTILE TILE;

class CBoard : public CScreen
{
private:
	bool allocated;
	
protected:
	TILE **data, **prevData;
	int width, height;
	
public:
	CBoard();
	virtual ~CBoard();
	
	int getWidth();
	int getHeight();
	void create(int width, int height);
	void destroy();
	TILE getTile(int x, int y);
	void setTile(int x, int y, TILE tile);
	void draw(int x, int y);
};