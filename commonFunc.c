#include <stdio.h>
#include "basicInfo.h"
#include "commonFunc.h"
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
		if (move >= 0 && move <= 3) validMove = 1;
	}
	return move;
}

int isArrUsed(struct Square arr){
	if (arr.used == 1)
		return 1;
	else
		return 0;
}

int isEmptyValue(struct Square arr){
	if (arr.value == 0)
		return 1;
	else
		return 0;
}

int isEqualofValue(struct Square A, struct Square B){
	if (A.value == B.value)
		return 1;
	else
		return 0;
}
int isPlayerLose(struct Squre m[][SIZE]){
	struct Pos empty[SIZE*SIZE];
	int cnt_empty = 0;
	cnt_empty = getEmptyCells(empty, m);

	if (cnt_empty > 0)
		return 0;

	else{
		if (playerLose(m))
			return 1;
		else
			return 0;
	}
	
}

int playerLose(struct Squre m[][SIZE]){
	struct Square temp_board[SIZE][SIZE];
	struct Pos empty[SIZE*SIZE];
	
	for (int i = 0; i < 4; i++){
		cpyBoard(temp_board, m);
		handleMove(i, temp_board);
		if (getEmptyCells(empty, temp_board) > 0)
			return 0;
	}

	return 1;
}

void cpyBoard(struct Square temp[][SIZE], struct Square m[][SIZE]){

	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			temp[i][j].used = m[i][j].used;
			temp[i][j].value = m[i][j].value;
		}
	}
}