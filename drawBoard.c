#include "drawBoard.h"
#include "commonFunc.h"
#include <time.h>

void draw(struct Square m[][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf("%4d ", m[i][j].value);
		}
		printf("\n");
	}
}/* 2차원 Matrix형태로 sqaure배열의 cell 위치 data를 갖는다. */

int generateRandom(int min, int max) {
	srand(time(NULL));
	return rand() % (max - min) + min;
}/* 매개변수 min과 max의 사이의 임의으; 수를 반환한다. */

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
}/* 매개변수 pos empty[] : Square 구조체 배열의 원소 중 value==0인 원소 인덱스 저장
    2중 반복문을 이용해 구조체 m 배열 원소의 value == 0인 원소를 탐색한다.
    value == 0인 원소의 인덱스 정보를 empty에 저장한다.
    반환값 n : Square 구조체 배열에서 value == 0인 원소의 개수
 */

void addRandomSquare(struct Square m[][SIZE]) {
	struct Pos empty[SIZE * SIZE];
	int random;
	int n = getEmptyCells(empty, m);
	if (n > 0) {
		random = generateRandom(0, n);
		m[empty[random].x][empty[random].y].value = 2;
	}
}/* 매개변수 m : Square 구조체 size*size 크기의 배열
    반환 값 : 없음
    Square 구조체 배열 m의 value == 0인 임의의 원소에 vlaue 값을 '2'로 초기화
*/

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
}/* 매개변수 m : 초기화 될 square 구조체 배열
    반환값 : 없음
    각 구조체 배열 원소의 멤버 변수 value와 used를 '0'으로 초기화
*/
void cleanCells(struct Square m[][SIZE]) {
	updateBoardCells(m, -1, 0);
}/* 매개변수 m : square 구조체 2차원 배열 m의 value와 used 변수들을 초기화시킴.
    반환값 : 없음
*/


