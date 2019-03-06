#include "tetris.h"

CTetris::CTetris()
{
}
CTetris::~CTetris()
{
}
BRICK &CTetris::getBrick()
{
	return brick;
}
void CTetris::createBrick(int shape)
{
	if(shape>=0 && shape<=11)
	{
		brick.shape=shape;
		brick.rotateState=0;
		brick.prevRotateState=brick.rotateState;
		brick.x=width/2;
		brick.y=0;
		brick.prevX=brick.x;
		brick.prevY=brick.y;
	}
}
bool CTetris::checkAround(int x, int y, int rotateState)
{
	COORD position;
	TILE tile;
	int i;
	
	for(i=0;i<5;i++)
	{
		position=_SHAPECOORD[brick.shape][rotateState][i];
		tile=getTile(x+position.X, y+position.Y);
		if(tile==_BRICK || tile==_NONE)
			return false;
	}
	
	return true;
}
bool CTetris::moveBrick(int x, int y, int rotateState)
{
	if(checkAround(x, y, rotateState))
	{
		brick.x=x;
		brick.y=y;
		brick.rotateState=rotateState;
		
		return true;
	}
	else
		return false;
}
void CTetris::putBrick(TILE tile)
{
	COORD position;
	int i;

	for(i=0;i<5;i++)
	{
		position=_SHAPECOORD[brick.shape][brick.prevRotateState][i];
		setTile(brick.prevX+position.X, brick.prevY+position.Y, _EMPTY);
	}
	for(i=0;i<5;i++)
	{
		position=_SHAPECOORD[brick.shape][brick.rotateState][i];
		setTile(brick.x+position.X, brick.y+position.Y, tile);
	}
	brick.prevRotateState=brick.rotateState;
	brick.prevX=brick.x;
	brick.prevY=brick.y;
}
int CTetris::removeFullLine()
{
	int x, y;
	int count=0;
	int i, j;

	for(y=0;y<height;y++)
	{
		for(x=0;x<width && getTile(x, y)!=_EMPTY;x++);
		if(x==width)
		{
			for(i=y;i>=1;i--)
			{
				for(j=0;j<width;j++)
					setTile(j, i, getTile(j, i-1));
			}
			for(j=0;j<width;j++)
				setTile(j, i, _EMPTY);
			count++;
		}
	}

	return count;
}
