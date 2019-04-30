#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define SIZE 4

enum directions { RIGHT, DOWN, LEFT, UP };
//directions 0 ->, 1 down,  2 <-, 3 up

struct Square {
	int value;
	int used;
};

struct Pos {
	int x;
	int y;
};

void draw(struct Square m[][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf("%4d ", m[i][j].value);
		}
		printf("\n");
	}
}

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
		if (!arr[i].value) continue;

		for (j = i; j < SIZE - 1; j++) {
			if (arr[j + 1].used) continue;
			if (!arr[j + 1].value) {
				rightShiftCell(arr, j);
			}
			else if (arr[j + 1].value == arr[j].value) {
				mergeCells(arr, j, j + 1);
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
	if (direction != RIGHT) doRotations(m, 4 - times);
}

int generateRandom(int min, int max) {
	return rand() % (max - min + 1) + min; // min ~ max 범위의 랜덤한 수를 리턴
}

int getEmptyCells(struct Pos empty[], struct Square m[][SIZE]) { //빈셀의 개수와 좌표를 얻기위한 함수
	int i, j; //for문 index
	int n = 0; //빈 셀의 개수를 저장할 변수
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) // 모든 셀을 방문하는 for문
			if (!m[i][j].value) { //셀의 value값이 0인 경우
				struct Pos temp; //임시 Pos 변수로 빈 셀의 좌표 값을 저장
				temp.x = i; //temp의 x값에 셀의 x좌표값을 넣음
				temp.y = j; //temp의 y값에 셀의 y좌표값을 넣음
				empty[n++] = temp; //empty배열에 temp값을 넣고 n에 1을 더해준다
			}
	return n; //빈 셀의 개수를 리턴
}

void addRandomSquare(struct Square m[][SIZE]) {
	struct Pos empty[SIZE * SIZE]; //value가 1인 cell의 Position(x, y좌표값)을 저장할 배열
	int random; //랜덤변수를 저장하기위한 변수
	int n = getEmptyCells(empty, m); //value가 1인 cell의 개수를 불러오며, empty배열에 빈 셀들의 좌표를 저장한다
	if (n > 0) { // 빈 셀이 있다면
		random = generateRandom(0, n); //0과 n사이의 랜덤 수 저장
		m[empty[random].x][empty[random].y].value = 2; //빈 셀들 중 하나를 랜덤으로 골라 그 셀의 value를 2로 변경
	}
}

int playerWon(struct Square m[][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (m[i][j].value == 2048) return 1;
		}
	}
	return 0;
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
	int i, randomSquares = 6;
	for (i = 0; i < randomSquares; i++) {
		addRandomSquare(m);
	}
}

void cleanCells(struct Square m[][SIZE]) {
	updateBoardCells(m, -1, 0);
}

int readMove() {
	int move, validMove = 0; // 사용자에게 이동방향을 입력받는 변수 move와 그 move가 유효한 move인지 아닌지 표시하는 flag인 validMove 선언
	while (!validMove) { //validMove가 0이면 반복
		printf("Make a move: moves right %d, down %d, left %d, up %d \n",
			RIGHT, DOWN, LEFT, UP); //사용자에게 이동 방향을 입력하라고 출력함
		scanf("%d", &move); //사용자에게 이동 방향을 입력받음
		if (move >= 0 && move < 3) validMove = 1; //이동 방향이 아래, 왼쪽, 오른쪽 중 하나이면 validMove를 1로 바꿔 while문을 빠져나감
	}
	return move; //입력받은 이동 방향을 리턴
}

int main() {
	struct Square board[SIZE][SIZE];
	initBoard(board);

	int move = 0;
	while (1) {
		draw(board);
		if (playerWon(board)) break;//

		addRandomSquare(board); // board의 빈 셀중 하나를 랜덤으로 골라 value를 2로 변경
		int move = readMove(); //이동 방향을 입력받음
		handleMove(move, board);
		cleanCells(board);//
	}

	printf("You won");
	return 0;
}
