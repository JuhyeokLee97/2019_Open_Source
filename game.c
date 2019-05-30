#include <stdio.h>
#include <stdlib.h>
#include "basicInfo.h"
#include "drawBoard.h"
#include "moveCells.h"


int main() {
	struct Square board[SIZE][SIZE];
	initBoard(board);

	int move = 0;
	while (TRUE) {
		system("cls");
		
		if (playerWon(board)) 
		{
			printf("You Won\n");
			break;
		}
		addRandomSquare(board);
		draw(board);

		move = readMove();
		handleMove(move, board);
		cleanCells(board);

		if(isPlayerLose(board)) 
		{
			printf("You Lose\n");
			break;
		}
	}
	return 0;
}

