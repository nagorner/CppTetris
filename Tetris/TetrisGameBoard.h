#pragma once
#include "MatrixUtils.h"
#include "TetFigures.h"
extern int CurrentFigure_RowPos;
extern int tHeight;
extern int tWidth;
void TetrisGame_Initialize();
void TetrisGame_Start();
void TetrisGame_Over();
void Tetris_AdditionToBoard();
bool Tetris_ApplyFigureToBoard(int rowNumber, FIGURE_OBJECT whichFigure, int whichAngle);
void Tetris_BoardPrint();
bool Tetris_GameProcess_MoveFigureToDown();
void Tetris_MoveFigureLeftOrRight(int dir);