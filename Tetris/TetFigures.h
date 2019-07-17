#pragma once

#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

#define FIGURE_WIDTH 4
#define FIGURE_HEIGHT 2
extern int TETRIS_CURRENT_FIGURE;
typedef int FIGURE_OBJECT[FIGURE_HEIGHT][FIGURE_WIDTH];


extern FIGURE_OBJECT* TETRIS_FIGURES[5];


int Tetris_SelectFigure();
void Tetris_InitializeFigures();