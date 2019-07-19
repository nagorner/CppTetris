#include "pch.h"
#include <iostream>
#include "MatrixUtils.h"
#include "TetFigures.h"
#include "TetrisGameBoard.h"
#include "ConsoleUtils.h"


using namespace std;
//aaa


int main()
{  
	    TetrisGame_Initialize();
		Tetris_BoardPrint();
		bool result=1;
		char c;
		char direction;
		while (true) {
			Tetris_AdditionToBoard();
			cout << endl;
			Tetris_BoardPrint();
			cout << endl;
			while (result)
			{
									
				cin >> direction;

				if (direction == 'q') { Tetris_MoveFigureLeftOrRight(-1); Tetris_BoardPrint();  
				cout << endl;
				}

				if (direction == 'w') { Tetris_MoveFigureLeftOrRight(1); Tetris_BoardPrint();
				cout << endl;
				}
				if(direction=='a'){
					result = Tetris_GameProcess_MoveFigureToDown();
					Tetris_BoardPrint();
					cout << endl;
				}
				if (direction == 'z') {
					CurrentAngle++;
				}
				
			}
			result = 1;
		}
	
}

