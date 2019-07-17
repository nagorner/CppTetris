#include "pch.h"
#include <iostream>
#include <vector>
#include <time.h>
#include "TetFigures.h"


FIGURE_OBJECT *TETRIS_FIGURES[5];

int TETRIS_CURRENT_FIGURE = 0;

int Tetris_SelectFigure()
{
	srand(time(NULL));
	TETRIS_CURRENT_FIGURE = rand() % 5;
	return TETRIS_CURRENT_FIGURE;
}

FIGURE_OBJECT Figure1 =
{
	{1,1,1,1},
	{0,0,0,0}
};

FIGURE_OBJECT Figure2 =
{
	{ 1,1,1,0 },
	{0, 1, 0,0}
};
FIGURE_OBJECT Figure3 =
{
	{0,1,1,0 },
	{0, 1,1,0 }
};

FIGURE_OBJECT Figure4 =
{
	{ 1,1,0,0 },
	{ 0,1,1,0 }
};
FIGURE_OBJECT Figure5 = {
	{0, 1,1,1 },
	{0, 0,0,1 }
};

void Tetris_InitializeFigures()
{
	

	TETRIS_FIGURES[0] = &Figure1;
	TETRIS_FIGURES[1] = &Figure2;
	TETRIS_FIGURES[2] = &Figure3;
	TETRIS_FIGURES[3] = &Figure4;
	TETRIS_FIGURES[4] = &Figure5;


}



