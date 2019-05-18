#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // sleep함수를 사용하기 위해 만듬. 삭제 필요
#include "basicInfo.h"
#include "drawBoard.h"
#include "moveCells.h"


int main() {
	struct Square board[SIZE][SIZE];
	initBoard(board);

	int move = 0;
	while (1) {
		system("cls");
		puts("--------Before-------");
		draw(board);
		struct Pos empty[SIZE * SIZE];
		if (playerWon(board)) break;

		printf("\tcnt_empty : %d\n", getEmptyCells(empty, board));
		addRandomSquare(board);

		puts("\n\n--------After(create New Value)-------");
		draw(board);
		printf("\tcnt_empty : %d\n", getEmptyCells(empty, board));

		int move = readMove();
		handleMove(move, board);
		cleanCells(board);

		if(playerLose(board)) 
		{
			printf("\t Final cnt_empty is %d\n", getEmptyCells(empty, board));
			Sleep(10000);
			break;
		}
	}

	printf("You won");
	Sleep(10000);
	return 0;
}

