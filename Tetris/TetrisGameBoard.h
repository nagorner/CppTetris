#pragma once
#include "MatrixUtils.h"
#include "TetFigures.h"
extern int CurrentFigure_RowPos;
extern int tHeight;
extern int tWidth;
extern int CurrentAngle;
extern int Game_Points;
void TetrisGame_Initialize();
void Point_Counter();
int Delta_Counter(FIGURE_OBJECT whichFigure, int whichAngle);
int Gamma_Counter(FIGURE_OBJECT whichFigure, int whichAngle);
void CurrentAngle_Change();
void TetrisGame_Start();
void TetrisGame_Over();
void Tetris_AdditionToBoard();
bool Tetris_ApplyFigureToBoard(int rowNumber, FIGURE_OBJECT whichFigure, int whichAngle);
void Tetris_BoardPrint();
bool Tetris_GameProcess_MoveFigureToDown();
void Tetris_MoveFigureLeftOrRight(int dir);