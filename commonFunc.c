#include <stdio.h>
#include <string.h> // memcpy함수를 사용하기 위해서.
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
	
	memcpy(&temp_board, &m, sizeof(struct Square));

	// 오른쪽 이동 가능한 경우
	handleMove(0, temp_board);
	if (getEmptyCells(empty, temp_board) > 0)
		return 0;

	// 아래쪽 이동 가능한 경우
	handleMove(1, temp_board);
	if (getEmptyCells(empty, temp_board) > 0)
		return 0;
	
	// 왼쪽 이동 가능한 경우
	handleMove(2, temp_board);
	if (getEmptyCells(empty, temp_board) > 0)
		return 0;

	// 위쪽 이동 가능한 경우
	handleMove(3, temp_board);
	if (getEmptyCells(empty, temp_board) > 0)
		return 0;

	return 1;
}