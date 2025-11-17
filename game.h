#include "cell.h"

#ifndef GAME_H
#define GAME_H


int cursor[2] = {0, 0};
int lcursor[2] = {0, 0};
bool gameOver = false;
bool win = false;


void moveCursor(int moveOn[2], struct Cell map[ROW][COL]){
	if (cursor[0] + moveOn[0] >= COL || cursor[1] + moveOn[1] >= ROW)
		return;
	if ((moveOn[0] + cursor[0]) < 0 || (moveOn[1] + cursor[1]) < 0)
		return;
	
	lcursor[1] = cursor[1];
	cursor[1] += moveOn[1];
	lcursor[0] = cursor[0];
	cursor[0] += moveOn[0];

	cursor[0] %= COL;
	cursor[1] %= ROW;

	/*
	int y = moveOn[1];
	for (int x=cursmoveOn[0]; x<COL; x++){
		if (!map[y][x].isOpen){
			lcursor[0] = cursor[0];
			cursor[0] = x;
			break;
		}
	}*/
}


bool revealCell(struct Cell map[ROW][COL], struct Cell *cell){
	int x = cell->x;
	int y = cell->y;
	if (cell->isFlag)
		return false;
	cell->isOpen = true;
	return cell->isMine;
}


void revealNearCells(struct Cell map[ROW][COL], int x, int y){}


#endif // GAME_H
