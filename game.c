#include <stdio.h>
#include <stdlib.h>
#include "basicInfo.h"
#include "drawBoard.h"
#include "moveCells.h"


int playerWon(struct Square m[][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (m[i][j].value == 2048) return 1;
		}
	}
	return 0;
}




int readMove() {
	int move, validMove = 0;
	while (!validMove) {
		printf("Make a move: moves right %d, down %d, left %d, up %d \n",
			RIGHT, DOWN, LEFT, UP);
		scanf("%d", &move);
		if (move >= 0 && move < 3) validMove = 1;
	}
	return move;
}

int main() {
	struct Square board[SIZE][SIZE];
	initBoard(board);

	int move = 0;
	while (1) {
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

