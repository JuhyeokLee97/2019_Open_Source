#ifndef __BASICINFO_H__

#define __BASICINFO_H__

#define SIZE 4
#define TRUE 1
#define FALSE 0

enum directions { RIGHT, DOWN, LEFT, UP };
//directions 0 ->, 1 down,  2 <-, 3 up

struct Square {
	int value;	// 사용자에게 보여주는 data이다.
	int used;	// 사용자에게 보여주는 data이다.
};/*2차원 Matrix형태로 square배열이 만들어진다. square하나가 cell 하나와 같다고 생각하면 된다.*/

struct Pos {
	int x;
	int y;
};/* 2차원 Matrix형태로 sqaure배열의 cell 위치 data를 갖는다. */
#endif