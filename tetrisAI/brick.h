#pragma once

const COORD _SHAPECOORD[][4][5]={
	{
		{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}, {2, 0}},
		{{0, -2}, {0, -1}, {0, 0}, {0, 1}, {0, 2}},
		{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}, {2, 0}},
		{{0, -2}, {0, -1}, {0, 0}, {0, 1}, {0, 2}}
	},
	{
		{{-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}},
		{{0, -1}, {0, 0}, {1, 0}, {0, 1}, {1, 1}},
		{{0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}},
		{{-1, -1}, {0, -1}, {-1, 0}, {0, 0}, {0, 1}}
	},
	{
		{{-1, 0}, {0, 0}, {1, 0}, {0, 1}, {1, 1}},
		{{0, -1}, {1, -1}, {0, 0}, {1, 0}, {0, 1}},
		{{-1, -1}, {0, -1}, {-1, 0}, {0, 0}, {1, 0}},
		{{0, -1}, {-1, 0}, {0, 0}, {-1, 1}, {0, 1}}
	},
	{
		{{-2, 0}, {-1, 0}, {0, 0}, {0, 1}, {0, 2}},
		{{0, 0}, {1, 0}, {2, 0}, {0, 1}, {0, 2}},
		{{0, -2}, {0, -1}, {0, 0}, {1, 0}, {2, 0}},
		{{0, -2}, {0, -1}, {-2, 0}, {-1, 0}, {0, 0}}
	},
	{
		{{-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {1, 1}},
		{{0, -1}, {1, -1}, {0, 0}, {0, 1}, {1, 1}},
		{{-1, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}},
		{{-1, -1}, {0, -1}, {0, 0}, {-1, 1}, {0, 1}}
	},
	{
		{{-1, 0}, {0, 0}, {1, 0}, {0, 1}, {0, 2}},
		{{0, -1}, {0, 0}, {1, 0}, {2, 0}, {0, 1}},
		{{0, -2}, {0, -1}, {-1, 0}, {0, 0}, {1, 0}},
		{{0, -1}, {-2, 0}, {-1, 0}, {0, 0}, {0, 1}}
	},
	{
		{{0, 0}, {1, 0}, {2, 0}, {-1, 1}, {0, 1}},
		{{0, -2}, {0, -1}, {0, 0}, {1, 0}, {1, 1}},
		{{0, -1}, {1, -1}, {-2, 0}, {-1, 0}, {0, 0}},
		{{-1, -1}, {-1, 0}, {0, 0}, {0, 1}, {0, 2}}
	},
	{
		{{-2, 0}, {-1, 0}, {0, 0}, {0, 1}, {1, 1}},
		{{1, -1}, {0, 0}, {1, 0}, {0, 1}, {0, 2}},
		{{-1, -1}, {0, -1}, {0, 0}, {1, 0}, {2, 0}},
		{{0, -2}, {0, -1}, {-1, 0}, {0, 0}, {-1, 1}}
	},
	{
		{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}, {1, 1}},
		{{0, -1}, {1, -1}, {0, 0}, {0, 1}, {0, 2}},
		{{-1, -1}, {-1, 0}, {0, 0}, {1, 0}, {2, 0}},
		{{0, -2}, {0, -1}, {0, 0}, {-1, 1}, {0, 1}}
	},
	{
		{{-1, 0}, {0, 0}, {1, 0}, {2, 0}, {-1, 1}},
		{{0, -2}, {0, -1}, {0, 0}, {0, 1}, {1, 1}},
		{{1, -1}, {-2, 0}, {-1, 0}, {0, 0}, {1, 0}},
		{{-1, -1}, {0, -1}, {0, 0}, {0, 1}, {0, 2}}
	},
	{
		{{-1, 0}, {0, 0}, {1, 0}, {2, 0}, {0, 1}},
		{{0, -2}, {0, -1}, {0, 0}, {1, 0}, {0, 1}},
		{{0, -1}, {-2, 0}, {-1, 0}, {0, 0}, {1, 0}},
		{{0, -1}, {-1, 0}, {0, 0}, {0, 1}, {0, 2}}
	},
	{
		{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}, {0, 1}},
		{{0, -1}, {0, 0}, {1, 0}, {0, 1}, {0, 2}},
		{{0, -1}, {-1, 0}, {0, 0}, {1, 0}, {2, 0}},
		{{0, -2}, {0, -1}, {-1, 0}, {0, 0}, {0, 1}}
	}
};

struct _tagBRICK
{
	int shape;
	int rotateState, prevRotateState;
	int x, y, prevX, prevY;
};
typedef struct _tagBRICK BRICK;
