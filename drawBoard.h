#include "basicInfo.h"
#ifndef __DRAWBOARD_H__

#define __DRAWBOARD_H__

void draw(struct Square m[][SIZE]);
int generateRandom(int min, int max);
int getEmptyCells(struct Pos empty[], struct Square m[][SIZE]);
void addRandomSquare(struct Square m[][SIZE]);
void updateBoardCells(struct Square m[][SIZE], int value, int used);
void initBoard(struct Square m[][SIZE]);
void cleanCells(struct Square m[][SIZE]);


#endif

