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
			if (m[i][j].value == 2048) return TRUE;
		}
	}
	return FALSE;
}

int readMove() {
	char move;
	int validMove = 0;
	while (isValidMove(validMove)) {
		printf("UP : W, LEFT : A, DOWN : S, RIGHT : D\n");
		printf("Move : ");
		scanf("%c", &move);

		getchar();
		switch (move)
		{
		case 'w':
		case 'W':
			move = UP;
			validMove = 1;
			break;
		case 'a':
		case 'A':
			move = LEFT;
			validMove = 1;
			break;
		case 's':
		case 'S':
			move = DOWN;
			validMove = 1;
			break;
		case 'D':
		case 'd':
			move = RIGHT;
			validMove = 1;
			break;
		default:
			break;
		}
	}
	return move;
}

int isArrUsed(struct Square arr){
	if (arr.used != EMPTY)
		return TRUE;
	else
		return FALSE;
}

int isEmptyValue(struct Square arr){
	if (arr.value != EMPTY)
		return FALSE;
	else
		return TRUE;
}

int isEqualofValue(struct Square A, struct Square B){
	if (A.value == B.value)
		return TRUE;
	else
		return FALSE;
}
int isPlayerLose(struct Squre m[][SIZE]){
	struct Pos empty[SIZE*SIZE];
	int cnt_empty = EMPTY;
	cnt_empty = getEmptyCells(empty, m);

	if (cnt_empty == EMPTY){
		if (playerLose(m))
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
	
}

int playerLose(struct Squre m[][SIZE]){
	struct Square temp_board[SIZE][SIZE];
	struct Pos empty[SIZE*SIZE];
	
	for (int i = 0; i < 4; i++){
		cpyBoard(temp_board, m);
		handleMove(i, temp_board);
		if (getEmptyCells(empty, temp_board) > EMPTY)
			return FALSE;
	}

	return TRUE;
}

void cpyBoard(struct Square temp[][SIZE], struct Square m[][SIZE]){
	// memcpy함수로 이용할 수 있으면 좋을 것 같다.

	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			temp[i][j].used = m[i][j].used;
			temp[i][j].value = m[i][j].value;
		}
	}
}

int isValidMove(int validMove){
	if (validMove == EMPTY)
		return TRUE;
	else
		return FALSE;
}