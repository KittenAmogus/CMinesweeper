#include <stdlib.h>
#include <time.h>
#include "cell.h"
#include "settings.h"

#ifndef GAME_H
#define GAME_H


int cursor[2] = {0, 0};
int lcursor[2] = {0, 0};
bool gameOver = true;
bool win = false;


int randint(int lb, int ub){
	srand(time(NULL));
	int randomNum = rand() % (ub - lb) + lb;
	return randomNum;
}


void genMines(struct Cell map[ROW][COL]){
	srand(time(NULL));
	int indices[ROW * COL];
    for (int i = 0; i < ROW * COL; i++) {
        indices[i] = i;
    }

    for (int i = (ROW * COL) - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int k = 0; k < MINES; k++) {
        int selected_1d_index = indices[k];
        int row = selected_1d_index / COL;
        int col = selected_1d_index % COL;
		if (row == cursor[1] && col == cursor[0]){
			k--;
			continue;
		}
		map[row][col].isMine = true;
    }
	gameOver = false;
}


void genNear(struct Cell map[ROW][COL]){
	for (int x=0; x<COL; x++){
		for (int y=0; y<COL; y++){
			struct Cell *cell = &map[y][x];

			if (cell->isMine)
				continue;

			for (int ax=x-1; ax<x+2; ax++){
				if (ax < 0 || ax >= COL)
					continue;
				for (int ay=y-1; ay<y+2; ay++){
					if (ay < 0 || ay >= ROW)
						continue;

					if (map[ay][ax].isMine){
						cell->near++;
					}
				}
			}
		}
	}
}


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
	if (cell->isFlag || cell->isOpen)
		return false;

	cell->isOpen = true;

	// revealNearCells(map, x, y);

	return cell->isMine;
}


#endif // GAME_H
