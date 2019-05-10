#include "basicInfo.h"
#ifndef __MOVECELLS_H__

#define __MOVECELLS_H__

void rightShiftCell(struct Square arr[], int currentPos);
void mergeCells(struct Square arr[], int initialPos, int finalPos);
void slideArrayToRight(struct Square arr[]);
void rotate(struct Square m[][SIZE]);
void doRotations(struct Square m[][SIZE], int times);
void handleMove(int direction, struct Square m[][SIZE]);

#endif // !__MOVECELLS_H__
