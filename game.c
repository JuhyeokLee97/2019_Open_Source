#include <stdio.h>
#include <stdlib.h>
#include "basicInfo.h"
#include "drawBoard.h"
#include "moveCells.h"


int main() {
	struct Square board[SIZE][SIZE];
	initBoard(board);

	int move = 0;
	while (1) {
		system("cls");
		draw(board);
		
		if (playerWon(board)) break;

		addRandomSquare(board);
		int move = readMove();
		handleMove(move, board);
		cleanCells(board);
	}

	printf("You won");
	return 0;
}

