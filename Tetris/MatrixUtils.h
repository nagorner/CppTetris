#pragma once

#define ARRAY_SIZE 10

void Matrix_FillbyValue(int Matr[ARRAY_SIZE][ARRAY_SIZE], int x);
void Matrix_FillZero(int Matr[ARRAY_SIZE][ARRAY_SIZE]);
void Matrix_Print(int Matr[ARRAY_SIZE][ARRAY_SIZE]);	
void Matrix_RotateAroundPoint(int Matr[ARRAY_SIZE][ARRAY_SIZE], double x, double y, double a, double pointOfRot, int valueToRotate, int valueToExclude);
bool Matrix_IsRowFilledByValue(int Matr[ARRAY_SIZE][ARRAY_SIZE], int row, int valueToCheck);	
void Matrix_DeleteRow(int Matr[ARRAY_SIZE][ARRAY_SIZE], int row);	
void DeleteAllFilledRows(int Matr[ARRAY_SIZE][ARRAY_SIZE]);
