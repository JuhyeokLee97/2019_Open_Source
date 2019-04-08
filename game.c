#include <stdio.h>
#include <stdlib.h>
#define SIZE 4

enum directions {RIGHT, DOWN, LEFT, UP};
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
