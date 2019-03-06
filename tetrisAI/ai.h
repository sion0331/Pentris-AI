#pragma once

#include "game.h"

#define _LOWEST_SCORE -10000000.0f

class CTetrisAI : public CTetris
{
private:
	bool attached;
	CGame *object;

public:
	double lineW;
	double heightW;
	double holeW;
	double blockageW;
	double bumpinessW;
	double wellW;
	
public:
	CTetrisAI();
	virtual ~CTetrisAI();
	
	void initialize(double lineW, double heightW, double holeW, double blockageW, double bumpinessW, double wellW);
	void attach(CGame *object);
	void detach();
	CGame *getObject();
	void getGameData();
	double calculate();
	double simulate(int x, int rotateState, int *resultY);
	void run();
	void test(int x, int y);
};
