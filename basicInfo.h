#ifndef __BASICINFO_H__

#define __BASICINFO_H__

#define SIZE 4

enum directions { RIGHT, DOWN, LEFT, UP };
//directions 0 ->, 1 down,  2 <-, 3 up

struct Square {
	int value;
	int used;
};

struct Pos {
	int x;
	int y;
};
#endif