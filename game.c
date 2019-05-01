#include <stdio.h>
#include <stdlib.h>
#define SIZE 4

enum directions {RIGHT, DOWN, LEFT, UP};
//(기존)directions 0 ->, 1 down,  2 <-, 3 up

//4*4 크기 게임판 중 한 블록(1*1)을 의미함
struct Square 
{
  int value; //특정한 블록에 저장된 값
  int used; //블록의 value가 다른 블록의 value와 덧셈연산을 수행했는지의 여부 판단(0: no, 1: yes)
};

//2차원 구조체 배열의 가로 인덱스(x)와 세로 인덱스(y)를 의미함 
struct Pos 
{
  int x;
  int y;
};

//위에서 설정한 초기값들을 반영해 콘솔창에 4*4 크기의 게임판을 출력
void draw(struct Square m[][SIZE]) {
  int i,j;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++)  {
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

//(기존)only works for right direction, so we need to rotate the board before
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

//무작위로 배열의 인덱스 번호를 선정 후 반환
int generateRandom(int min, int max) {
  return rand()%(max-min+1) + min;
}

//2차원 구조체 배열 중, 멤버변수 value 값이 0인 인덱스의 가로, 세로 인덱스를 저장 후 총 개수 반환
int getEmptyCells(struct Pos empty[], struct Square m[][SIZE]) {
  int i,j;
  int n = 0;
  for(i = 0; i < SIZE; i++)
    for(j = 0; j < SIZE; j++)
      if (!m[i][j].value) //value의 값이 0인 경우(빈 블록) 
	  {
        struct Pos temp;
        temp.x = i;
        temp.y = j;
        empty[n++] = temp; //가로, 세로 인덱스 값을 저장
      }
  return n; //총 개수
}

//처음 콘솔창에서 시작 블록을 출력할 인덱스 선정 및 value값 2를 저장 
void addRandomSquare(struct Square m[][SIZE]) {
  struct Pos empty[SIZE * SIZE];
  int random;
  int n = getEmptyCells(empty, m); //함수 호출
  if (n > 0) {
    random = generateRandom(0, n); //함수 호출
    m[empty[random].x][empty[random].y].value = 2; //임의로 선정된 인덱스 안의 값에 따라 초기값 '2' 저장
  }
}

//게임의 승리 조건인 value값이 2048인 블록 유무 검사
int playerWon(struct Square m[][SIZE]) {
  int i, j;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      if (m[i][j].value == 2048) return 1;
    }
  }
  return 0;
}

//각 구조체 블록의 멤버변수들을 0으로 초기화
void updateBoardCells(struct Square m[][SIZE], int value, int used) {
  int i,j;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      if (value >= 0) // 연산이 된 값은 제외 
		 m[i][j].value = value;
      if (used >= 0) 
		 m[i][j].used = used;
    }
  }
}

//생성한 게임판의 값들을 초기화
void initBoard(struct Square m[][SIZE]) {
  updateBoardCells(m, 0, 0); //함수 호출
  int i, randomSquares = 6; //게임 시작화면에서 값이 출력될 블록의 개수 
  for (i = 0; i < randomSquares; i++) // 새롭게 생성할 블록의 개수만큼 반복 
  {
    addRandomSquare(m); //함수 호출
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
  struct Square board[SIZE][SIZE]; //4*4 크기의 게임판 생성
  initBoard(board); //함수 호출

  int move = 0;
  while(1) {
    draw(board);
    if (playerWon(board)) break; //조건문 안이 TRUE이면 while문 탈출

    addRandomSquare(board);
    int move = readMove();
    handleMove(move, board);
    cleanCells(board);
  }

  printf("You won");
  return 0;
}
