#pragma once

#include "board.h"
#include "brick.h"

class CTetris : public CBoard
{
	friend class CTetrisAI;
protected:
	BRICK brick;
	
public:
	CTetris();
	virtual ~CTetris();
	
	BRICK &getBrick();
	void createBrick(int shape);
	bool checkAround(int x, int y, int rotateState);
	bool moveBrick(int x, int y, int rotateState);
	void putBrick(TILE tile=_BRICK);
	int removeFullLine();
};
