#include "board.h"

CBoard::CBoard()
{
	allocated=false;
}
CBoard::~CBoard()
{
	if(allocated)
		destroy();
}
void CBoard::create(int width, int height)
{
	if(!allocated)
	{
		int i, j;
		
		CBoard::width=width;
		CBoard::height=height;
		data=new TILE *[height+2];
		prevData=new TILE *[height+2];
		for(i=0;i<height+2;i++)
		{
			data[i]=new TILE[width+2];
			prevData[i]=new TILE[width+2];
		}
		for(i=0;i<height+2;i++)
		{
			for(j=0;j<width+2;j++)
			{
				if(i==0 || i==height+1 || j==0 || j==width+1)
					data[i][j]=_WALL;
				else
					data[i][j]=_EMPTY;
			}
		}
		allocated=true;
	}
}
void CBoard::destroy()
{
	if(allocated)
	{
		int i;
		
		for(i=0;i<height+2;i++)
		{
			delete [] data[i];
			delete [] prevData[i];
		}
		delete [] data;
		delete [] prevData;
		allocated=false;
	}
}
int CBoard::getWidth()
{
	if(allocated)
		return width;
	else
		return 0;
}
int CBoard::getHeight()
{
	if(allocated)
		return height;
	else
		return 0;
}
TILE CBoard::getTile(int x, int y)
{
	if(allocated && x>=0 && y>=0 && x<width && y<height)
		return data[y+1][x+1];
	else
		return _NONE;
}
void CBoard::setTile(int x, int y, TILE tile)
{
	if(allocated && x>=0 && y>=0 && x<width && y<height)
		data[y+1][x+1]=tile;
}
void CBoard::draw(int x, int y)
{
	if(allocated)
	{
		int i, j;
		
		for(i=0;i<height+2;i++)
		{
			for(j=0;j<width+2;j++)
			{
				if(data[i][j]!=prevData[i][j])
				{
					setCursorPosition(x+j*2, y+i);
					switch(data[i][j])
					{
					case _EMPTY:
						setTextAttribute(0x08);
						printf("¢Æ");
						break;
					case _UNSUREBRICK:
						setTextAttribute(0x0A);
						printf("¡à");
						break;
					case _BRICK:
						setTextAttribute(0x0A);
						printf("¡á");
						break;
					case _WALL:
						setTextAttribute(0x0E);
						printf("¢Ã");
						break;
					case _NONE:
						printf("¡¡");
						break;
					}
					prevData[i][j]=data[i][j];
				}
			}
		}
	}
}
