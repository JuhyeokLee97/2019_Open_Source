#include "basicInfo.h"

#ifndef __COMMONFUNC_H__
#define __COMMONFUNC_h__

int playerWon(struct Square m[][SIZE]);
int readMove();
int isArrUsed(struct Square arr);
int isEmptyValue(struct Square arr);
int isEqualofValue(struct Square A, struct Square B);
int isPlayerLose(struct Squre m[][SIZE]);
int playerLose(struct Squre m[][SIZE]);
void cpyBoard(struct Square temp[][SIZE], struct Square m[][SIZE]);
int isValidMove(int validMove);
int EmptyCellExists(struct Squre m[][SIZE]);
#endif
