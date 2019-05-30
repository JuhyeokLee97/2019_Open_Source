#include "moveCells.h"
#include "commonFunc.h"

void rightShiftCell(struct Square arr[], int currentPos) {
	arr[currentPos + 1].value = arr[currentPos].value;
	arr[currentPos].value = 0;
}/* 매개변수 arr : Square 구조체 1차원 배열
    매개변수 currentPos : 오른쪽으로 이동할 배열 원소의 인덱스
    반환값 : 없음
    currentPos위치의 배열 원소를 currentPos + 1위치로 이동한다.
*/

void mergeCells(struct Square arr[], int initialPos, int finalPos) {
	arr[finalPos].value *= 2;
	arr[finalPos].used = 1;
	arr[initialPos].value = 0;
}/* 매개변수 arr : Square 구조체 1차원 배열
    매개변수 initialPos : 옮겨질 Square 구조체 배열 원소의 인덱스
    매개변수 finalPos : initialPos에서 finalPos 인덱스 위치로 값이 더해진다.
    반환값 : 없음
    arr[initialPos].value값을 arr[finalPos].value값에 더한다.
*/

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
}/* 함수 실행 예시
  ====[Before Matrix]====
  a11   a12   a13   a14
  a21   a22   a23   a24
  a31   a32   a33   a34
  a41   a42   a43   a44
  ====[After Matrix]====
  a14   a24   a34   a44
  a13   a23   a33   a43
  a12   a22   a32   a42
  a11   a21   a31   a41
*/

void doRotations(struct Square m[][SIZE], int times) {
	int i;
	for (i = 0; i < times; i++) {
		rotate(m);
	}
}/*매개변수 time : 반시계 방향으로 회전할 횟수
    반환값 : 없음
    Be called by function of 'handleMove'. 
    파라미터 2차원 배열 m을 times번 반시계 방향으로 90도 회전시킨다. 
	*/

void handleMove(int direction, struct Square m[][SIZE]) {
	int i;
	int times = direction;	// direction파라미터가 정수 값을 갖고, times변수에 반시계방향으로 회전할 횟수를 저장한다.


	doRotations(m, times);
	for (i = 0; i < SIZE; i++) {
		slideArrayToRight(m[i]);
	}
	if (direction != RIGHT) doRotations(m, 4 - times); // isRight(int)
}

