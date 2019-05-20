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
		
		if (playerWon(board)) 
		{
			printf("You Won\n");
			break;
		}
		addRandomSquare(board);
		draw(board);

		int move = readMove();
		handleMove(move, board);
		cleanCells(board);

		if(isPlayerLose(board)) 
		{
			printf("You Lose\n");
			break;
		}
	}
	puts("\tThe End\n");
	return 0;
}

