#include "ai.h"
#include<conio.h>

CTetrisAI::CTetrisAI()
{
	attached=false;
}
CTetrisAI::~CTetrisAI()
{
	if(attached)
		detach();
}
void CTetrisAI::initialize(double lineW, double heightW, double holeW, double blockageW, double bumpinessW, double wellW)
{
	CTetrisAI::lineW=lineW;
	CTetrisAI::heightW=heightW;
	CTetrisAI::holeW=holeW;
	CTetrisAI::blockageW=blockageW;
	CTetrisAI::bumpinessW=bumpinessW;
	CTetrisAI::wellW=wellW;
}
void CTetrisAI::attach(CGame *object)
{
	if(!attached)
	{
		CTetrisAI::object=object;
		create(object->getWidth(), object->getHeight());
		attached=true;
	}
}
void CTetrisAI::detach()
{
	if(attached)
	{
		destroy();
		object=NULL;
		attached=false;
	}
}
CGame *CTetrisAI::getObject()
{
	if(attached)
		return object;
	else
		return NULL;
}
double CTetrisAI::calculate()
{
	if(attached)
	{
		int lines=0;
		int *heights=new int[width], maxHeight=0;
		int holes=0;
		int blockages=0;
		int bumps=0;
		int well, wells=0;
		TILE tile;
		bool flag;
		int i, j;

		memset(heights, 0, sizeof(int)*width);
		for(i=0;i<height;i++)
		{
			flag=true;
			for(j=0;j<width;j++)
			{
				tile=getTile(j, i);
				if(tile==_EMPTY)
				{
					if(flag)
						flag=false;
					if(heights[j]!=0)
						holes++;
				}
				else if(tile==_BRICK || tile==_UNSUREBRICK)
				{
					if(heights[j]==0)
					{
						heights[j]=height-i;
						if(heights[j]>maxHeight)
							maxHeight=heights[j];
					}
				}
			}
			if(flag)
				lines++;
		}
		for(i=0;i<width;i++)
		{
			flag=false;
			for(j=height-1;j>=0;j--)
			{
				tile=getTile(i, j);
				if(tile==_EMPTY)
				{
					if(!flag)
						flag=true;
				}
				if((tile==_UNSUREBRICK || tile==_BRICK) && flag)
					blockages++;
			}
			flag=true;
			well=height;
			if(i<width-1)
			{
				flag=flag && ((signed)heights[i+1]-(signed)heights[i]>=4);
				if((signed)heights[i+1]-(signed)heights[i]>=4)
					well=min(well, heights[i+1]-heights[i]);
			}
			if(i>0)
			{
				bumps+=abs((signed)heights[i]-(signed)heights[i-1]);
				flag=flag && ((signed)heights[i-1]-(signed)heights[i]>=4);
				if((signed)heights[i-1]-(signed)heights[i]>=4)
					well=min(well, heights[i-1]-heights[i]);
			}
			if(flag)
				wells+=well-3;
		}
		delete heights;

		/*setTextAttribute(0x0F);
		setCursorPosition(48, 1);
		printf("line: %-4d", lines);
		setCursorPosition(48, 2);
		printf("height: %-4d", maxHeight);
		setCursorPosition(48, 3);
		printf("hole: %-4d", holes);
		setCursorPosition(48, 4);
		printf("blockage: %-4d", blockages);
		setCursorPosition(48, 5);
		printf("bump: %-4d", bumps);
		setCursorPosition(48, 6);
		printf("well: %-4d", wells);*/
		//getch();
		
		return lineW*lines+heightW*maxHeight+holeW*holes+blockageW*blockages+bumpinessW*bumps+wellW*wells;
	}
	else
		return _LOWEST_SCORE;
}
double CTetrisAI::simulate(int x, int rotateState, int *resultY)
{
	if(attached)
	{
		double score;
		int y;
		
		for(y=0;!checkAround(x, y+1, rotateState) && y<height;y++);
		if(y==height)
			return _LOWEST_SCORE;
		for(;checkAround(x, y+1, rotateState) && y<height;y++);
		*resultY=y;
		brick.x=x;
		brick.y=y;
		brick.rotateState=rotateState;
		putBrick(_UNSUREBRICK);
		//draw(48, 1);
		score=calculate();
		putBrick(_EMPTY);

		return score;
	}
	else
		return _LOWEST_SCORE;
}
void CTetrisAI::run()
{
	if(attached)
	{
		int maxX, maxY, maxRotateState;
		int resultY;
		double maxScore=_LOWEST_SCORE, score;
		int i, j;
		
		for(i=0;i<4;i++)
		{
			for(j=0;j<width;j++)
			{
				score=simulate(j, i, &resultY);
				if(score>maxScore)
				{
					maxX=j;
					maxY=resultY;
					maxRotateState=i;
					maxScore=score;
				}
			}
		}
		//setCursorPosition(94, 7);
		//printf("maxX: %-3d, maxY: %-3d, maxRotateState: %-3d", maxX, maxY, maxRotateState);
		((CTetris *)object)->moveBrick(maxX, maxY, maxRotateState);
		object->putBrick(_BRICK);
		object->draw();
		//object->putBrick(_BRICK);
	}
}
void CTetrisAI::getGameData()
{
	if(attached  && object->width==width && object->height==height)
	{
		int i;
		
		for(i=0;i<height+2;i++)
			memcpy(data[i], object->data[i], sizeof(TILE)*(width+2));
		brick=object->brick;
	}
}
void CTetrisAI::test(int x, int y)
{
	setCursorPosition(x, y);
	printf("%.2lf %.2lf %.2lf %.2lf %.2lf %.2lf", lineW, heightW, holeW, blockageW, bumpinessW, wellW);
}