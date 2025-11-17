#include <stdio.h>
#include "game.h"

#ifndef MAP_H
#define MAP_H



char* getColor(struct Cell cell){

	if (!cell.isOpen){
		if (cell.isFlag)
			return "\x1b[102;30m";
		else
			return "\x1b[0m";
	}
	if (cell.isMine)
		return "\x1b[1;91m";

	int num = cell.near;
	switch (num){
		case 0:
			return "\x1b[0m";
		case 1:
			return "\x1b[104;30m";
		case 2:
			return "\x1b[42;30m";
		case 3:
			return "\x1b[101;30m";
		case 4:
			return "\x1b[44;30m";
		case 5:
			return "\x1b[41;30m";
		case 6:
			return "\x1b[106;30m";
		case 7:
			return "\x1b[105;30m";
		case 8:
			return "\x1b[100;30m";
		default:
			return "\x1b[1;30m";
	}
}


char* getString(struct Cell cell){
	char str[3] = " @ ";
	if (cursor[0] == cell.x && cursor[1] == cell.y){
		str[0] = '[';
		str[2] = ']';
	}
	if (!cell.isOpen){
		if (cell.isFlag)
			str[1] = 'F';
		else
			str[1] = '#';
		char* strp = str;
		return strp;
	}
	if (!cell.isMine){
		if (cell.near > 0)
			str[1] = (char)(48 + cell.near);
		else
			str[1] = ' ';
		char* strp = str;
		return strp;
	}

	char* strp = str;
	return strp;
}

/*

,---, ,---,
| * | | @ |
'---' '---'

,---, ,---, ,---,
| - | | # | |###|
'---' '---' '---'


,---,---,---,---,
| 2 | 1 |   |###|
|---+---+---+---|
| * | * |   |###|
|---+---+---+---|
| 3 |   | 8 | # |
|---+---+---+---|
| F | F | * |   |
'---'---'---'---'

|2|1| |#|
|*|*| |#|
|3| |8|#|
|F|F|*|#|

 */

void genMap(struct Cell map[ROW][COL], struct Cell lmap[ROW][COL]){
		for (int y=0; y<ROW; y++){
			for (int x=0; x<COL; x++){
				struct Cell cell = {false, false, false, 0, x, y};
				map[y][x] = cell;
				lmap[y][x] = cell;
			}
		}
}

void draw_one(struct Cell map[ROW][COL]){
	printf("\x1b[H\x1b[2J");  // \x1b[90m");
	
	printf("╭───");
	for (int x=1; x<COL; x++){
		printf("┬───");
	}
	printf("╮\n\r");  // ",\x1b[90m\n\r");
	
	for (int y=0; y<ROW; y++){
		printf("│");  // "\x1b[90m|");

		for (int x=0; x<COL; x++){
			printf("%s%s", getColor(map[y][x]), getString(map[y][x]));
			printf("\x1b[0m│");
		};
		printf("\x1b[0m\n\r├");  // \r\x1b[90m|");
		
		if (y + 1 < ROW){
			for (int x=0; x<COL - 1; x++){
				printf("───┼");
			}
			printf("───┤\x1b[0m\n\r");
		}
		else {
			printf("\r╰");  // \r\x1b[90m'");
			for (int x=0; x<COL - 1; x++){
				printf("───┴");
			}
			printf("───╯");
		}
	}
	
	printf("\n\r");
}


void draw(struct Cell map[ROW][COL], struct Cell lmap[ROW][COL]){
	for (int y=0; y<ROW; y++){
		for (int x=0; x<COL; x++){
			if (
					map[y][x].isFlag != lmap[y][x].isFlag ||
					map[y][x].isOpen != lmap[y][x].isOpen ||
					(cursor[0] == x && cursor[1] == y) ||
					(lcursor[0] == x && lcursor[1] == y)
							){
				printf("\x1b[%d;%dH", 2 + (y * 2), (x * 4) + 2);
				printf("%s%s\x1b[0m", getColor(map[y][x]), getString(map[y][x]));
			}
		}
	}
	printf("\x1b[0m\x1b[%d;%dH\n\r", (ROW * 2) + 1, 1);
}


#endif // MAP_H

