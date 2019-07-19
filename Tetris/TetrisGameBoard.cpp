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
#define ANGLE_270 3

int CurrentAngle = 0;
int CurrentFigure_RowPos = 0;
int CurrentFigure_ColumnPos = 0;

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

void Tetris_TrueHeightAndWidth(FIGURE_OBJECT TetrisFigure, int whichAngle) {

	tHeight = 0;
	tWidth = 0;

	int maxI = -1000;
	int maxJ = -1000;
	int minJ = 1000;
	int minI = 1000;


	if (whichAngle == ANGLE_0 || whichAngle == ANGLE_180) {
		for (int i = 0; i < FIGURE_HEIGHT; i++) {

			for (int j = 0; j < FIGURE_WIDTH; j++) {
				if (TetrisFigure[i][j] == 1)
				{
					if (i > maxI) maxI = i;
					if (i < minI) minI = i;
					if (j > maxJ) maxJ = j;
					if (j < minJ)minJ = j;
				}
			}

		}
		tWidth = maxJ - minJ+1;
		tHeight = maxI - minI+1;

	}


	if (whichAngle == ANGLE_90 || whichAngle == ANGLE_270) {
		for (int i = 0; i < FIGURE_HEIGHT; i++) {

			for (int j = 0; j < FIGURE_WIDTH; j++) {
				if (TetrisFigure[i][j] == 1)
				{
					if (i > maxI) maxI = i;
					if (i < minI) minI = i;
					if (j > maxJ) maxJ = j;
					if (j < minJ)minJ = j;
				}
			}

		}
		tHeight = maxJ - minJ+1;
		tWidth = maxI - minI+1;

	}
}
void Tetris_DeleteFigureFromBoard() {

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		for (int j = 0; j < ARRAY_SIZE; j++) {
			if (GAME_BOARD[i][j] == CELL_ACTIVE) //if game board element == 2 it means freez figure
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
void Tetris_ClearTheLine(int line) {
	while (line != 0) {
		for (int i = 0; i < ARRAY_SIZE; i++) {
			GAME_BOARD[line][i] = GAME_BOARD[line - 1][i];

		}
		line--;
	}
	if (line == 0) {
		for (int i = 0; i < ARRAY_SIZE; i++) {
			GAME_BOARD[line][i] == 0;
		}
	}
}
void Tetris_CheckTheLines() {
	int counter = 0;
	for (int i = 0; i < ARRAY_SIZE; i++) {
		for (int j = 0; j < ARRAY_SIZE; j++) {
			if (GAME_BOARD[i][j] == 2) counter++;
		}
		if (counter == ARRAY_SIZE) Tetris_ClearTheLine(i);
		counter = 0;
	}
}

bool Tetris_CanApplyFigureToBoard(int rowNumber, int columnNumber, FIGURE_OBJECT whichFigure, int whichAngle)
{
	Tetris_TrueHeightAndWidth(whichFigure, whichAngle);
	if (rowNumber + tHeight > ARRAY_SIZE || columnNumber + tWidth > ARRAY_SIZE || columnNumber < 0)
		return false;
	if (whichAngle == ANGLE_0) {
		for (int i = 0; i < FIGURE_HEIGHT; i++)
			for (int j = 0; j < FIGURE_WIDTH; j++)
				if (whichFigure[i][j] != CELL_EMPTY)
					if (GAME_BOARD[i + rowNumber][j + columnNumber] != CELL_EMPTY)
						return false;
	}
	if (whichAngle == ANGLE_270) {
		for (int i = 0; i < FIGURE_HEIGHT; i++)
			for (int j = 0; j < FIGURE_WIDTH; j++)
				if (whichFigure[i][j] != CELL_EMPTY)
					if (GAME_BOARD[j + rowNumber][i + columnNumber] != CELL_EMPTY)
						return false;
	}
	if (whichAngle == ANGLE_180) {
		for (int i = 0; i < FIGURE_HEIGHT; i++)
			for (int j = 0; j < FIGURE_WIDTH; j++)
				if (whichFigure[i][j] != CELL_EMPTY)
					if (GAME_BOARD[FIGURE_HEIGHT - i + rowNumber-1][j + columnNumber] != CELL_EMPTY)
						return false;
	}
	if (whichAngle == ANGLE_90) {
		for (int i = 0; i < FIGURE_HEIGHT; i++)
			for (int j = 0; j < FIGURE_WIDTH; j++)
				if (whichFigure[i][j] != CELL_EMPTY)
					if (GAME_BOARD[FIGURE_WIDTH-j+rowNumber-1][i+columnNumber] != CELL_EMPTY)
						return false;
	}
	return true; //can apply, all game board elements for figure are zero
}

void Tetris_ApplyFigureToBoard(int rowNumber, int columnNumber, FIGURE_OBJECT whichFigure, int whichAngle)
{
	//if you entered here, it means that figure can be applied
	
	if (whichAngle == ANGLE_0) {
		for (int i = 0; i < FIGURE_HEIGHT; i++)
			for (int j = 0; j < FIGURE_WIDTH; j++)
				if (whichFigure[i][j] == CELL_ACTIVE)
					GAME_BOARD[i + rowNumber][j + columnNumber] = CELL_ACTIVE;

	}

	if (whichAngle == ANGLE_270) {
		for (int i = 0; i < FIGURE_HEIGHT; i++)
			for (int j = 0; j < FIGURE_WIDTH; j++)
				if (whichFigure[i][j] == CELL_ACTIVE)
					GAME_BOARD[j + rowNumber][i + columnNumber] = CELL_ACTIVE;
	}
	
	if (whichAngle == ANGLE_180) {
		for (int i = 0; i < FIGURE_HEIGHT; i++)
			for (int j = 0; j < FIGURE_WIDTH; j++)
				if (whichFigure[i][j] == CELL_ACTIVE)
					GAME_BOARD[FIGURE_HEIGHT - i + rowNumber-1][j + columnNumber] = CELL_ACTIVE;

	}
	if (whichAngle == ANGLE_90) {
		for (int i = 0; i < FIGURE_HEIGHT; i++)
			for (int j = 0; j < FIGURE_WIDTH; j++)
				if (whichFigure[i][j] == CELL_ACTIVE)
					GAME_BOARD[FIGURE_WIDTH - j + rowNumber-1][i + columnNumber] = CELL_ACTIVE;

	}
}
void Tetris_MoveFigureLeftOrRight(int dir) {
	bool result;
	CurrentFigure_ColumnPos += dir;

	Tetris_DeleteFigureFromBoard();

	result = Tetris_CanApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure, CurrentAngle);
	if (!result)
	{
		CurrentFigure_ColumnPos -= dir;
	}

	Tetris_ApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure, CurrentAngle);
}

void Tetris_AdditionToBoard() {
	CurrentAngle = 0;
	CurrentFigure_RowPos = 0;
	Tetris_SelectFigure();

	CurrentFigure = TETRIS_FIGURES[TETRIS_CURRENT_FIGURE];
	CurrentFigure_ColumnPos = ARRAY_SIZE / 4 + 1;

	bool canApply = Tetris_CanApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure, CurrentAngle);

	Tetris_ApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure, CurrentAngle);

	if (!canApply)
		TetrisGame_Over();
}
bool Tetris_GameProcess_MoveFigureToDown()
{
	if (CurrentAngle == 4) CurrentAngle = 0;
	Tetris_DeleteFigureFromBoard();
	CurrentFigure_RowPos++;

	bool canApply = Tetris_CanApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure, CurrentAngle);

	if (canApply)
		Tetris_ApplyFigureToBoard(CurrentFigure_RowPos, CurrentFigure_ColumnPos, *CurrentFigure, CurrentAngle);
	else
	{
		//old one was deleted
		Tetris_ApplyFigureToBoard(CurrentFigure_RowPos - 1, CurrentFigure_ColumnPos, *CurrentFigure, CurrentAngle);
		Tetris_FreezeFigureFromBoard();
		Tetris_CheckTheLines();
		return false;
	}

	return true;
}
