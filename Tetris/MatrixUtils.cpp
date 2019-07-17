#include "pch.h"
#include <iostream>
#include "MatrixUtils.h"
#include <stdio.h> 
#include <stdlib.h> 
#include "TetFigures.h"
#include "TetrisGameBoard.h"
using namespace std;

void Matrix_FillbyValue(int Matr[ARRAY_SIZE][ARRAY_SIZE], int x)
{
	for (int i = 0; i < ARRAY_SIZE; i++) {
		for (int j = 0; j < ARRAY_SIZE; j++) {
			Matr[i][j] = x;
		}
	}
}

void Matrix_FillZero(int Matr[ARRAY_SIZE][ARRAY_SIZE]) {
	Matrix_FillbyValue(Matr, 0);
}

void Matrix_Print(int Matr[ARRAY_SIZE][ARRAY_SIZE]) {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		for (int j = 0; j < ARRAY_SIZE; j++) {
			cout << Matr[i][j] << ' ';
		}
		cout << endl;
	}
}

void Matrix_RotateAroundPoint(int Matr[ARRAY_SIZE][ARRAY_SIZE], double x, double y, double a, double pointOfRot,int valueToRotate, int valueToExclude) {
	int Matr2[ARRAY_SIZE][ARRAY_SIZE];
	Matrix_FillbyValue(Matr2, 0);
	double x1, y1;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		for (int j = 0; j < ARRAY_SIZE; j++)
		{
			if (Matr[i][j] == valueToRotate) {
				x1 = (x - pointOfRot)*  cos(a / 360 * 2 * 3.14) - (y - pointOfRot) * sin(a / 360 * 2 * 3.14);
				x1 = x1 + pointOfRot;
				y1 = (y - pointOfRot) * cos(a / 360 * 2 * 3.14) + (x - pointOfRot) * sin(a / 360 * 2 * 3.14);
				y1 = y1 + pointOfRot;
				if (x1 < 0) x1 = 0;
				if (x1 >= ARRAY_SIZE) x1 = ARRAY_SIZE - 1;

				if (y1 < 0) y1 = 0;
				if (y1 >= ARRAY_SIZE) y1 = ARRAY_SIZE - 1;
				Matr2[int(y1)][int(x1)] = valueToRotate;
			}

		}
	}

	for (int i = 0; i < ARRAY_SIZE; i++) {
		for (int j = 0; j < ARRAY_SIZE; j++) {
			if (Matr[i][j] != valueToExclude)
				Matr[i][j] = Matr2[i][j];
		}
	}
}

bool Matrix_IsRowFilledByValue(int Matr[ARRAY_SIZE][ARRAY_SIZE], int row, int valueToCheck) {
	int count = 0;
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (Matr[row][i] = valueToCheck) count++;
		if (count == ARRAY_SIZE) row++;
	}
	return row;
}

void Matrix_DeleteRow(int Matr[ARRAY_SIZE][ARRAY_SIZE], int row) {
	for (int i = row; i >= 0; i++) {
		for (int j = 0; j < ARRAY_SIZE; j++) {
			if (i != 0) Matr[i][j] = Matr[i - 1][j];
			else Matr[i][j] = 0;
		}

	}
}
void DeleteAllFilledRows(int Matr[ARRAY_SIZE][ARRAY_SIZE]) {
	int IsRowFilled;
	for (int row = 0; row < ARRAY_SIZE; row++) {
		IsRowFilled = Matrix_IsRowFilledByValue(Matr, row,2);
		if (IsRowFilled) {
			Matrix_DeleteRow(Matr, row);
		}
	}
}