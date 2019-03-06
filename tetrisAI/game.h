#pragma once

#include "tetris.h"

enum _tagDIRECTION
{
	_LEFT,
	_RIGHT,
	_DOWN,
	_DOWNMOST
};
typedef enum _tagDIRECTION DIRECTION;

class CGame : public CTetris
{
protected:
	int boardX, boardY;
	unsigned long speed;
	unsigned long tick;
	bool show;
	
public:
	CGame();
	virtual ~CGame();
	
	void initialize(int boardX=0, int boardY=0, unsigned long speed=500, bool show=true);
	bool createBrick(int shape);
	bool createBrick();
	bool checkAround();
	bool moveBrick(DIRECTION direction);
	bool rotate();
	bool step();
	void gameOver();
	void draw();
};
