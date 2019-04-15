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

    for(j = i; j < SIZE - 1; j++) {
      if (arr[j+1].used) continue;
      if (!arr[j+1].value) {
        rightShiftCell(arr, j);
      } else if (arr[j+1].value == arr[j].value) {
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
}/* 함수 실행 예시 (when i++)
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
};/* Be called by function of 'handleMove'. 파라미터 2차원 배열 m을 times번 반시계 방향으로 회전시킨다. */

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
}

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
}

void cleanCells(struct Square m[][SIZE]) {
  updateBoardCells(m, -1, 0);
}

int readMove() {
  int move, validMove = 0;
  while (!validMove) {
    printf("Make a move: moves right %d, down %d, left %d, up %d \n",
           RIGHT, DOWN, LEFT, UP);
    scanf("%d", &move);
    if (move >= 0 && move < 3) validMove = 1;
  }
  return move;
}

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
