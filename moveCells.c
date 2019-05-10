#include "moveCells.h"
#include "commonFunc.h"

void rightShiftCell(struct Square arr[], int currentPos) {
	arr[currentPos + 1].value = arr[currentPos].value;
	arr[currentPos].value = 0;
}

void mergeCells(struct Square arr[], int initialPos, int finalPos) {
	arr[finalPos].value *= 2;
	arr[finalPos].used = 1;
	arr[initialPos].value = 0;
}

//only works for right direction, so we need to rotate the board before
void slideArrayToRight(struct Square arr[]) {
	int i, j;

	for (i = SIZE - 2; i >= 0; i--) {
		if (isEmptyValue(arr[i])) continue;

		for (j = i; j < SIZE - 1; j++) {
			if (isArrUsed(arr[j+1])) continue;  // isArrUsed(struct)
			if (isEmptyValue(arr[j+1])) { // isEmptyValue(struct)
				rightShiftCell(arr, j);
			}
			else if (isEqualofValue(arr[j+1], arr[j])) {    // isEqual(int, int)
				mergeCells(arr, j, j + 1);
                j++;
			}
		}
	}
}

void rotate(struct Square m[][SIZE]) {
	int i, j, n = SIZE;
	struct Square temp;

	for (i = 0; i < n / 2; i++) {
		for (j = i; j < n - i - 1; j++) {
			temp = m[i][j];
			m[i][j] = m[j][n - i - 1];
			m[j][n - i - 1] = m[n - i - 1][n - j - 1];
			m[n - i - 1][n - j - 1] = m[n - j - 1][i];
			m[n - j - 1][i] = temp;
		}
	}
}

void doRotations(struct Square m[][SIZE], int times) {
	int i;
	for (i = 0; i < times; i++) {
		rotate(m);
	}
};

void handleMove(int direction, struct Square m[][SIZE]) {
	int i;
	int times = direction;

	doRotations(m, times);
	for (i = 0; i < SIZE; i++) {
		slideArrayToRight(m[i]);
	}
	if (direction != RIGHT) doRotations(m, 4 - times); // isRight(int)
}

