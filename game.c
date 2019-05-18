#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // sleep함수를 사용하기 위해 만듬. 삭제 필요
#include <string.h> // memcpy함수를 사용하기 위해 만듬.
#include "basicInfo.h"
#include "drawBoard.h"
#include "moveCells.h"


int main() {
	struct Square board[SIZE][SIZE];
	initBoard(board);

	int move = 0;
	while (1) {
		system("cls");
		// puts("--------Before-------");
		// draw(board);
		
		if (playerWon(board)) break;

		struct Pos empty[SIZE * SIZE];
		//printf("\tcnt_empty : %d\n", getEmptyCells(empty, board));
		addRandomSquare(board);

		puts("\n\n--------After(create New Value)-------");
		draw(board);
		printf("\tcnt_empty : %d\n", getEmptyCells(empty, board));

		int move = readMove();
		handleMove(move, board);
		cleanCells(board);

		if(playerLose(board)) 
		{
			struct Square temp_board[SIZE][SIZE];
			memcpy(&temp_board, &board, sizeof(struct Square));
			//각 방향 이동.
			handleMove(0, temp_board);
			if (!playerLose(temp_board))
				continue;
			memcpy(&temp_board, &board, sizeof(struct Square));
			//각 방향 이동.
			handleMove(1, temp_board);
			if (!playerLose(temp_board))
				continue;	
			memcpy(&temp_board, &board, sizeof(struct Square));
			//각 방향 이동.
			handleMove(2, temp_board);
			if (!playerLose(temp_board))
				continue;
			memcpy(&temp_board, &board, sizeof(struct Square));
			//각 방향 이동.
			handleMove(3, temp_board);
			if (!playerLose(temp_board))
				continue;
			
			printf("\t Final cnt_empty is %d\n", getEmptyCells(empty, board));
			Sleep(10000);
			break;
		}
	}

	printf("You won");
	Sleep(10000);
	return 0;
}

