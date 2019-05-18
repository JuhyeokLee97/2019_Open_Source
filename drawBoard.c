#include "drawBoard.h"
#include "commonFunc.h"

void draw(struct Square m[][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf("%4d ", m[i][j].value);
		}
		printf("\n");
	}
}

int generateRandom(int min, int max) {
	srand();
	return rand() % (max - min) + min;
}

int getEmptyCells(struct Pos empty[], struct Square m[][SIZE]) {
	int i, j;
	int n = 0;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			if (isEmptyValue(m[i][j])) {
				struct Pos temp;
				temp.x = i;
				temp.y = j;
				empty[n++] = temp;
			}
	return n;
}

void addRandomSquare(struct Square m[][SIZE]) {
	struct Pos empty[SIZE * SIZE];
	int random;
	int n = getEmptyCells(empty, m);
	if (n > 0) {
		random = generateRandom(0, n);
		m[empty[random].x][empty[random].y].value = 2;
	}
}

void updateBoardCells(struct Square m[][SIZE], int value, int used) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (value >= 0) m[i][j].value = value;
			if (used >= 0) m[i][j].used = used;
		}
	}
}

void initBoard(struct Square m[][SIZE]) {
	updateBoardCells(m, 0, 0);
	int i, randomSquares = 3;
	for (i = 0; i < randomSquares; i++) {
		addRandomSquare(m);
	}
}
void cleanCells(struct Square m[][SIZE]) {
	updateBoardCells(m, -1, 0);
}


