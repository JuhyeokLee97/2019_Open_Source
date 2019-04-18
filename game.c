///////////////////////////////////////////////////////////////////////
//  #TODO
//    1. slideArrayToRight함수 내 mergeCells함수 부분에 대해서 mergeCells함수가 호출 되었을 시 반복문의 인덱스 값에 +1을 해줘야 합쳐진 셀을 한번 더 합쳐지지 않는다.
//    2. 게임 킬 때 마다 나오는 cell의 모양이 일정하다. 즉 srand()함수를 이용해야 한다.
//  #TODO/MAYBE-LATER
//    1. main함수 지역변수 move 가 필요하지 않다 -> 삭제 필요 (BC. memory 낭비)
//    2. 무한 루프 제거
//    3. SlideArrayToRight 함수 내 조건문의 조건식 함수화
//    4. getEmptyCells 함수 내 조건문의 조건식 함수화
//    5. updateBoardCells 함수 내 조건문의 조건식 함수화
//
///////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4  // 2048게임에 기본 틀은 4*4형태이므로 바꾸지 않는 것이 좋다.

enum directions {RIGHT, DOWN, LEFT, UP};
//directions 0 ->, 1 down,  2 <-, 3 up

struct Square {
  int value;  // 사용자에게 보여주는 data이다.
  int used;   // value 값을 연산할 때 flag변수로 사용된다.
};/*2차원 Matrix형태로 square배열이 만들어진다. square하나가 cell 하나와 같다고 생각하면 된다.*/

struct Pos {
  int x;
  int y;
};/* 2차원 Matrix형태로 sqaure배열의 cell 위치 data를 갖는다. */

void draw(struct Square m[][SIZE]) {
  int i,j;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++)  {
      printf("%4d ", m[i][j].value);
    }
    printf("\n");
  }
}/* sqaure.value 값을 4*4 Matrix 형태로 콘솔에 출력해준다. */

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
    if (!arr[i].value) continue;

    for(j = i; j < SIZE - 1; j++) {
      if (arr[j+1].used) continue;
      if (!arr[j+1].value) {  // case : arr[j].value != 0 && arr[j+1] == 0
        rightShiftCell(arr, j);
      } else if (arr[j+1].value == arr[j].value) {  // case : arr[j].value != 0 && arr[j+1] != 0
        mergeCells(arr, j, j + 1);
      }
    }
  }
}

void rotate(struct Square m[][SIZE]) {
  int i, j, n = SIZE;
  struct Square temp;

  for (i = 0; i < n / 2; i++){
    for (j = i; j < n - i - 1; j++){
      temp = m[i][j];
      m[i][j] = m[j][n-i-1];
      m[j][n-i-1] = m[n-i-1][n-j-1];
      m[n-i-1][n-j-1] = m[n-j-1][i];
      m[n-j-1][i] = temp;
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
};/*매개변수 time : 반시계 방향으로 회전할 횟수
    반환값 : 없음
    Be called by function of 'handleMove'. 
    파라미터 2차원 배열 m을 times번 반시계 방향으로 90도 회전시킨다. */

void handleMove(int direction, struct Square m[][SIZE]) {
  int i;
  int times = direction;  // direction파라미터가 정수 값을 갖고, times변수에 반시계방향으로 회전할 횟수를 저장한다.

  doRotations(m, times);
  for (i = 0; i < SIZE; i++) {
    slideArrayToRight(m[i]);
  }
  if (direction != RIGHT) doRotations(m, 4 - times);
}

int generateRandom(int min, int max) {
  return rand()%(max-min+1) + min;
}/* 매개변수 min과 max의 사이의 임의으 수를 반환한다. */

int getEmptyCells(struct Pos empty[], struct Square m[][SIZE]) {
  int i,j;
  int n = 0;
  for(i = 0; i < SIZE; i++)
    for(j = 0; j < SIZE; j++)
      if (!m[i][j].value) {
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
  struct Pos empty[SIZE * SIZE];  // Square 구조체 m배열의 원소 중 value == 0인 원소의 인덱스(위치) 저장
  int random;
  int n = getEmptyCells(empty, m);
  if (n > 0) {  
    random = generateRandom(0, n);
    m[empty[random].x][empty[random].y].value = 2;  // Square구조체 배열 m의 원소 중 value==0인 임의의 원소에 value 변수 '2'로 초기화
  }
}/* 매개변수 m : Square 구조체 size*size 크기의 배열
    반환 값 : 없음
    Square 구조체 배열 m의 value == 0인 임의의 원소에 vlaue 값을 '2'로 초기화
*/

int playerWon(struct Square m[][SIZE]) {
  int i, j;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      if (m[i][j].value == 2048) return 1;
    }
  }
  return 0;
}/* 매개변수 m : size*size square구조체 2차원 배열
  2차원 반복문을 통해서 각 원소의 value 값들을 탐색한다.
  value값이 2048인 경우 '1'을 반환한다.
  반환값 1 : 게임을 이겼음을 의미
  반환값 0 : 게임을 끝나지 않았음을 의미
 */

void updateBoardCells(struct Square m[][SIZE], int value, int used) {
  int i,j;
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
}/* 매개변수 m : 초기화 될 square 구조체 배열
    반환값 : 없음
    각 구조체 배열 원소의 멤버 변수 value와 used를 '0'으로 초기화
*/

void cleanCells(struct Square m[][SIZE]) {
  updateBoardCells(m, -1, 0);
}/* 매개변수 m : square 구조체 2차원 배열 m의 value와 used 변수들을 초기화시킴.
    반환값 : 없음
*/

int readMove() {
  int move, validMove = 0;
  while (!validMove) {
    printf("Make a move: moves right %d, down %d, left %d, up %d \n",
           RIGHT, DOWN, LEFT, UP);
    scanf("%d", &move);
    if (move >= 0 && move < 3) validMove = 1;
  }
  return move;
}/* 반환값 move : 입력 받은 키값 반환.
    사용자의 키보드 입력값을 반환한다.
*/

int main() {
  struct Square board[SIZE][SIZE];
  initBoard(board);

  int move = 0;
  while(1) {
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
