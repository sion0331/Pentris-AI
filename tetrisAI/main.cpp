#include "main.h"
#include <algorithm>
using namespace std;

#define _COUNT 69

double randf(int min, int max)
{
	int v=rand()%(abs(max-min)*1000+1)+min*1000;
	return (double)v/1000.0f;
}

struct _tagTestSet
{
	bool alive;
	CGame *game;
	CTetrisAI *ai;
	int removedLine;
	bool operator <(_tagTestSet &other)
	{
		return removedLine>other.removedLine;
	}
};
typedef struct _tagTestSet TestSet;

TestSet set[_COUNT];
double chromosome[15];
double value[10];

TestSet showing;

	int main(void)
{
	bool next;
	int cnt;
	int repeated;
	int i;
	
	/*
	system("mode con:cols=55 lines=27");
	srand(GetTickCount());
	Sleep(4000);

	showing.game=new CGame;
	showing.ai=new CTetrisAI;
	showing.game->initialize(0, 0, 0, true);
	showing.ai->initialize(1.763100, -0.515344, -6.537646, -0.404700, -0.637501, -4.3363700);
	
	showing.alive=true;
	showing.game->destroy();
	showing.game->create(15, 25);
	showing.ai->detach();
	showing.ai->attach(showing.game);
	showing.removedLine=0;

	do
	{
		next=false;
		int shape=rand()%12;
		
		if(showing.alive)
		{
			if(!showing.game->createBrick(shape))
				showing.alive=false;

			else
			{
				COORD position={35, 25};
				HANDLE consoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleCursorPosition(consoleOutput, position);

				printf("Cleared Line: %d", showing.removedLine);

				showing.ai->getGameData();
				showing.ai->run();
				showing.removedLine+=showing.game->removeFullLine();
			}
			next=true;
		}
	}while(next);

	Sleep(10000);
	return 0;*/

	system("mode con:cols=70 lines=1000");
	srand(GetTickCount());
	
	for(i=0;i<_COUNT;i++)
	{
		set[i].game=new CGame;
		set[i].ai=new CTetrisAI;
		set[i].game->initialize(0, 0, 0, false);
	}
	for(i=0;i<_COUNT;i++)
	{
		set[i].ai->initialize(randf(-10, 10), randf(-10,10), randf(-10, 10), randf(-10, 10), randf(-10, 10), randf(-10, 10));
		Sleep(50);
	}

	printf("start!\n");
	for(repeated=0;repeated<1000;repeated++)
	{
		for(i=0;i<_COUNT;i++)
		{
			set[i].alive=true;
			set[i].game->destroy();
			set[i].game->create(15, 25);
			set[i].ai->detach();
			set[i].ai->attach(set[i].game);
			set[i].removedLine=0;
		}
		do
		{
			next=false;
			int shape=rand()%12;
			for(i=0;i<_COUNT;i++)
			{
				if(set[i].alive)
				{
					if(!set[i].game->createBrick(shape))
						set[i].alive=false;
					else
					{
						set[i].ai->getGameData();
						set[i].ai->run();
						set[i].removedLine+=set[i].game->removeFullLine();
					}
					next=true;
				}
			}
		}while(next);
		sort(set, set+_COUNT);
		printf("%d  %d %f %f %f %f %f %f\n", set[0].removedLine, 
			repeated,
			set[0].ai->lineW,
			set[0].ai->heightW,
			set[0].ai->holeW,
			set[0].ai->blockageW,
			set[0].ai->bumpinessW,
			set[0].ai->wellW);


		//reproduction 10 


		//mutation 
		//10% variance on each chromosome 
		//add 10*12=120 to the population 
		cnt=0; 
		for(i=0;i<3;i++){
			double lineW, heightW, holeW, blockageW, bumpinessW, wellW;

			lineW=(set[i].ai->lineW);
			heightW=(set[i].ai->heightW);
			holeW=(set[i].ai->holeW);
			blockageW=(set[i].ai->blockageW);
			bumpinessW=(set[i].ai->bumpinessW);
			wellW=(set[i].ai->wellW);

			set[3+cnt].ai->initialize(lineW+lineW/10, heightW, holeW, blockageW, bumpinessW, wellW);
			set[3+cnt+1].ai->initialize(lineW, heightW+heightW/10, holeW, blockageW, bumpinessW, wellW);
			set[3+cnt+2].ai->initialize(lineW, heightW, holeW+holeW/10, blockageW, bumpinessW, wellW);
			set[3+cnt+3].ai->initialize(lineW, heightW, holeW, blockageW+blockageW/10, bumpinessW, wellW);
			set[3+cnt+4].ai->initialize(lineW, heightW, holeW, blockageW, bumpinessW+bumpinessW/10, wellW);
			set[3+cnt+5].ai->initialize(lineW, heightW, holeW, blockageW, bumpinessW, wellW+wellW/10);
			
			set[3+cnt+6].ai->initialize(lineW-lineW/10, heightW, holeW, blockageW, bumpinessW, wellW);
			set[3+cnt+7].ai->initialize(lineW, heightW-heightW/10, holeW, blockageW, bumpinessW, wellW);
			set[3+cnt+8].ai->initialize(lineW, heightW, holeW-holeW/10, blockageW, bumpinessW, wellW);
			set[3+cnt+9].ai->initialize(lineW, heightW, holeW, blockageW-blockageW/10, bumpinessW, wellW);
			set[3+cnt+10].ai->initialize(lineW, heightW, holeW, blockageW, bumpinessW-bumpinessW/10, wellW);
			set[3+cnt+11].ai->initialize(lineW, heightW, holeW, blockageW, bumpinessW, wellW-wellW/10);
			
			cnt+=12;
		}//set = 0~65


		
		//crossover
		//Top 1 set crossovers with other 9 sets
		//Exchange 1 chromosome of top 1 set with one of other sets
		//add 6*9 =54 
		cnt=0;
		for(i=1; i<3; i++){
			set[39 + cnt].ai->initialize(set[i].ai->lineW, set[0].ai->heightW, set[0].ai->holeW, set[0].ai->blockageW, set[0].ai->bumpinessW, set[0].ai->wellW); 
			set[39 + cnt +1].ai->initialize(set[0].ai->lineW, set[i].ai->heightW, set[0].ai->holeW, set[0].ai->blockageW, set[0].ai->bumpinessW, set[0].ai->wellW); 
			set[39 + cnt +2].ai->initialize(set[0].ai->lineW, set[0].ai->heightW, set[i].ai->holeW, set[0].ai->blockageW, set[0].ai->bumpinessW, set[0].ai->wellW); 
			set[39 + cnt +3].ai->initialize(set[0].ai->lineW, set[0].ai->heightW, set[0].ai->holeW, set[i].ai->blockageW, set[0].ai->bumpinessW, set[0].ai->wellW); 
			set[39 + cnt +4].ai->initialize(set[0].ai->lineW, set[0].ai->heightW, set[0].ai->holeW, set[0].ai->blockageW, set[i].ai->bumpinessW, set[0].ai->wellW); 
			set[39 + cnt +5].ai->initialize(set[0].ai->lineW, set[0].ai->heightW, set[0].ai->holeW, set[0].ai->blockageW, set[0].ai->bumpinessW, set[i].ai->wellW); 

			cnt+=6;
		}//set = 89


		
		//Random
		//one chromosome of each set is randomly determined 
		//6*10= 60
		cnt=0;
		for(i=0;i<3;i++)
		{
			set[51+cnt].ai->initialize(randf(-10,10), set[i].ai->heightW, set[i].ai->holeW, set[i].ai->blockageW, set[i].ai->bumpinessW, set[i].ai->wellW); 
			Sleep(50);

			set[51+cnt+1].ai->initialize(set[i].ai->lineW,  randf(-10,10), set[i].ai->holeW, set[i].ai->blockageW, set[i].ai->bumpinessW, set[i].ai->wellW); 
			Sleep(50);
			
			set[51+cnt+2].ai->initialize(set[i].ai->lineW, set[i].ai->heightW, randf(-10,10), set[i].ai->blockageW, set[i].ai->bumpinessW, set[i].ai->wellW); 
			Sleep(50);
			
			set[51+cnt+3].ai->initialize(set[i].ai->lineW, set[i].ai->heightW, set[i].ai->holeW,  randf(-10,10), set[i].ai->bumpinessW, set[i].ai->wellW); 
			Sleep(50);
			
			set[51+cnt+4].ai->initialize(set[i].ai->lineW, set[i].ai->heightW, set[i].ai->holeW, set[i].ai->blockageW, randf(-10,10), set[i].ai->wellW); 
			Sleep(50);
			
			set[51+cnt+5].ai->initialize(set[i].ai->lineW, set[i].ai->heightW, set[i].ai->holeW, set[i].ai->blockageW, set[i].ai->bumpinessW,  randf(-10,10)); 
			Sleep(50);

			cnt+=6;
		}//set=0~244

	}
	return 0;
}