#include <stdio.h> 
#include <stdlib.h> 
#include "MatrixUtils.h"
#include "TetFigures.h"
#include "TetrisGameBoard.h"
int GAME_BOARD[ARRAY_SIZE][ARRAY_SIZE];


#define CELL_FREEZE 2
#define CELL_ACTIVE 1
#define CELL_EMPTY 0

#define ANGLE_0 0
#define ANGLE_90 1
#define ANGLE_180 2
#define ANGLE_270 2

int CurrentFigure_RowPos=0;
int CurrentFigure_ColumnPos=0;

int tHeight;
int tWidth;

FIGURE_OBJECT *CurrentFigure;

void TetrisGame_Initialize()
{
	Matrix_FillbyValue(GAME_BOARD, 0);
	Tetris_InitializeFigures();
}

void Tetris_BoardPrint()
{
	Matrix_Print(GAME_BOARD);
}

void TetrisGame_Start()
{
	cout << "Starting the game";
}

void TetrisGame_Over()
{
	cout << "Game Over";
	exit(0);
}
/*void Tetris_TrueHighAndWidth(FIGURE_OBJECT TetrisFigure) {
	int width[2]{ 0,0 };
	for (int i = 0; i < FIGURE_HEIGHT; i++) {
		for (int j = 0; j < FIGURE_WIDTH; j++) {
			if (TetrisFigure[i][j] == 1) {
				width[i]++;
			}
		}
	}
	if (width[1] > width[2]) tWidth = width[1];
	else if (width[1] <= width[2]) tWidth = width[2];

	if (width[1] > 0 && width[2] > 0) tHeight = 2;
	else tHeight = 1;

}*/

void Tetris_TrueHeightAndWidth(FIGURE_OBJECT TetrisFigure) {
	
	tHeight = 0;
	tWidth = 0;

	for (int i = 0; i < FIGURE_HEIGHT; i++) {

		int Width=0;

		for (int j = 0; j < FIGURE_WIDTH; j++) {
			if(TetrisFigure[i][j]==1)
			Width++;
		}
		if (Width > tWidth) tWidth = Width;
	}
	for (int i = 0; i < FIGURE_WIDTH; i++) 
	{
		int Height = 0;
		for (int j = 0; j < FIGURE_HEIGHT; j++) {
			if (TetrisFigure[j][i] == 1)
				Height++;
		}
		if (Height > tHeight) tHeight = Height;
	}

}

void Tetris_DeleteFigureFromBoard() {
	
	for (int i = 0; i < ARRAY_SIZE; i++) 
	{
		for (int j = 0; j < ARRAY_SIZE; j++) {
			if(GAME_BOARD[i][j]==CELL_ACTIVE) //if game board element == 2 it means freez figure
				GAME_BOARD[i][j] = CELL_EMPTY;
		}
	}
}


void Tetris_FreezeFigureFromBoard() {

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		for (int j = 0; j < ARRAY_SIZE; j++) {
			if (GAME_BOARD[i][j] == CELL_ACTIVE) //if game board element == 2 it means freez figure
				GAME_BOARD[i][j] = CELL_FREEZE;
		}
	}
}

bool Tetris_CanApplyFigureToBoard(int rowNumber, int columnNumber, FIGURE_OBJECT whichFigure, int whichAngle)
{
	Tetris_TrueHeightAndWidth(whichFigure);
	if (rowNumber + tHeight > ARRAY_SIZE || columnNumber + tWidth > ARRAY_SIZE || columnNumber < 0)
		return false;

	for (int i = 0; i < FIGURE_HEIGHT; i++) 
		for (int j = 0; j < FIGURE_WIDTH; j++) 
			if (whichFigure[i][j]!=CELL_EMPTY)
				if (GAME_BOARD[i + rowNumber][j + columnNumber] != CELL_EMPTY)
					return false;

		return true; //can apply, all game board elements for figure are zero
}

void Tetris_ApplyFigureToBoard(int rowNumber, int columnNumber, FIGURE_OBJECT whichFigure, int whichAngle)
{
	 //if you entered here, it means that figure can be applied

	for (int i = 0; i < FIGURE_HEIGHT; i++) {
		for (int j = 0; j < FIGURE_WIDTH; j++) {
			if (whichFigure[i][j] == CELL_ACTIVE)
			{
				GAME_BOARD[i + rowNumber][j + columnNumber] = CELL_ACTIVE;
			}
		}
	}	
}
void Tetris_MoveFigureLeftOrRight(int dir) {
	bool result;
	CurrentFigure_ColumnPos+=dir;
	
	Tetris_DeleteFigureFromBoard();

	result=Tetris_CanApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure, 0);
	if (!result) 
	{
		CurrentFigure_ColumnPos -= dir;
	}
	
	Tetris_ApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure,0);		
}

void Tetris_AdditionToBoard() {
	CurrentFigure_RowPos = 0;
	Tetris_SelectFigure();

	CurrentFigure = TETRIS_FIGURES[TETRIS_CURRENT_FIGURE];
	CurrentFigure_ColumnPos = ARRAY_SIZE / 4 + 1;

	bool canApply = Tetris_CanApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure, 0);

	Tetris_ApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure,0);

	if (!canApply)
		TetrisGame_Over();
}
bool Tetris_GameProcess_MoveFigureToDown()
{
	Tetris_DeleteFigureFromBoard();
	CurrentFigure_RowPos++;

	bool canApply = Tetris_CanApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure, 0);

	if (canApply)
		Tetris_ApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure, 0);
	else
	{
		//old one was deleted
		Tetris_ApplyFigureToBoard(CurrentFigure_RowPos-1, CurrentFigure_ColumnPos, *CurrentFigure, 0);
		Tetris_FreezeFigureFromBoard();
		return false;
	}

	return true;
}
	