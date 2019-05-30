#include "basicInfo.h"
#ifndef __DRAWBOARD_H__

#define __DRAWBOARD_H__

void draw(struct Square m[][SIZE]);     // 2차원 Matrix 형태로 square배열의 데이터를 콘솔에 출력한다.
int generateRandom(int min, int max);   // min과 max 사이의 임의의 수를 반환한다.
int getEmptyCells(struct Pos empty[], struct Square m[][SIZE]);
void addRandomSquare(struct Square m[][SIZE]);  // Square 구조체 배열 m의 value == 0인 임의의 원소에 vlaue 값을 '2'로 초기화
void updateBoardCells(struct Square m[][SIZE], int value, int used);
void initBoard(struct Square m[][SIZE]);
void cleanCells(struct Square m[][SIZE]);


#endif

