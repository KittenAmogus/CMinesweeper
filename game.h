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



bool genMines(struct Cell map[ROW][COL]){
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

	int repeats = 0;
    for (int k = 0; k < MINES; k++) {
        int selected_1d_index = indices[k];
        int row = selected_1d_index / COL;
        int col = selected_1d_index % COL;
		if (row == cursor[1] && col == cursor[0]){
			repeats++;
			k--;
			if (repeats > 5){
				return false;
			}
			continue;
		}
		map[row][col].isMine = true;
    }
	gameOver = false;
	return true;
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

void revealNearCells(struct Cell map[ROW][COL],
				struct Cell *initialCell){
	if (initialCell == NULL || initialCell->isMine)
		return;

	struct Cell *queue[ROW * COL];
	int head = 0;
	int tail = 0;
	queue[tail++] = initialCell;

	while (head < tail){
		struct Cell *cell = queue[head++];

		if (cell == NULL || cell->isOpen)
			continue;

		if (!cell->isFlag)
			cell->isOpen = true;

		if (cell->near > 0)
			continue;

		for (int dy = -1; dy <= 1; dy++){
			for (int dx = -1; dx <= 1; dx++){
				if (dx == 0 && dy == 0)
					continue;

				int ny = cell->y + dy;
				int nx = cell->x + dx;
				if (ny < 0 || ny >= ROW || nx < 0 || nx >= COL)
					continue;

				struct Cell *nb = &map[ny][nx];

				if (tail < ROW * COL && tail + 1 < ROW * COL + 8 && !nb->isMine && !nb->isFlag && !nb->isOpen){
					queue[tail++] = nb;
					// nb->isOpen = true;
				}
			}
		}
	}
}

bool revealCell(struct Cell map[ROW][COL], struct Cell *cell){
	int x = cell->x;
	int y = cell->y;
	if (cell->isFlag || cell->isOpen)
		return false;

	if (cell->isMine){
		cell->isOpen = true;
		return true;
	}
	// cell->isOpen = true;

	revealNearCells(map, cell);

	return cell->isMine;
}


void gameOverFunc(struct Cell map[ROW][COL]){
	for (int x=0; x<COL; x++){
		for (int y=0; y<ROW; y++){
			if (map[y][x].isMine){
				struct Cell *cell = &map[y][x];
				cell->isOpen = true;
			}
		}
	}
}


#endif // GAME_H
