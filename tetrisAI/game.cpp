#include "game.h"

CGame::CGame()
{
	srand(GetTickCount());
	tick=0;
}
CGame::~CGame()
{
}
void CGame::initialize(int boardX, int boardY, unsigned long speed, bool show)
{
	CGame::boardX=boardX;
	CGame::boardY=boardY;
	CGame::speed=speed;
	CGame::show=show;
}
bool CGame::createBrick(int shape)
{
	if(shape>=0 && shape<=11)
		CTetris::createBrick(shape);
	else
		createBrick();
	if(!checkAround())
		return false;
	else
	{
		putBrick(_UNSUREBRICK);
		draw();
		tick=GetTickCount();

		return true;
	}
}
bool CGame::createBrick()
{
	return createBrick(rand()%12);
}
bool CGame::checkAround()
{
	return CTetris::checkAround(brick.x, brick.y, brick.rotateState);
}
bool CGame::moveBrick(DIRECTION direction)
{
	bool result=false, downMost=false;
	
	switch(direction)
	{
	case _LEFT:
		result=CTetris::moveBrick(brick.x-1, brick.y, brick.rotateState);
		break;
	case _RIGHT:
		result=CTetris::moveBrick(brick.x+1, brick.y, brick.rotateState);
		break;
	case _DOWN:
		result=CTetris::moveBrick(brick.x, brick.y+1, brick.rotateState);
		if(!result)
			downMost=true;
		break;
	case _DOWNMOST:
		for(;CTetris::moveBrick(brick.x, brick.y+1, brick.rotateState););
		downMost=true;
		break;
	}
	if(downMost)
		putBrick();
	else if(result)
		putBrick(_UNSUREBRICK);
	draw();
	
	return result;
}
bool CGame::rotate()
{
	int tempRotateState=brick.rotateState+1>3?0:brick.rotateState+1;
	bool result=false;
	
	if(CTetris::moveBrick(brick.x, brick.y, tempRotateState))
	{
		putBrick(_UNSUREBRICK);
		draw();
		result=true;
	}
	
	return result;
}
bool CGame::step()
{
	unsigned long tick=GetTickCount();
	bool result=true;
	
	if(tick-CGame::tick>=speed)
	{
		CGame::tick=tick;
		if(!moveBrick(_DOWN))
		{
			putBrick();
			result=false;
		}
		draw();
	}
	
	return result;
}
void CGame::gameOver()
{
}
void CGame::draw()
{
	if(show)
		CTetris::draw(boardX, boardY);
}