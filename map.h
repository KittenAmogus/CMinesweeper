#include <stdio.h>
#include <math.h>
#include "game.h"
#include "cell.h"


#ifndef MAP_H
#define MAP_H


void setPos(int x, int y){
	printf("\x1b[%d;%dH",
	(2 + 2 * y), (2 + 4 * x));
}


char* getColor(struct Cell cell){
	if (cursor[0] == cell.x && cursor[1] == cell.y)
		return "\x1b[93;1m";

	if (!cell.isOpen){
		if (!cell.isFlag)
			return "\x1b[30;40m";
		return "\x1b[102;30m";
	}

	if (cell.isMine){
		if (gameOver){
			return "\x1b[1;91m";
		}
		return "\x1b[101;30m";
	}

	switch (cell.near){
		case 0:
			return "\x1b[37;47m";
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
			return "";
	}
}


void printString(struct Cell cell){
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
		printf(strp);
		return;
	}
	if (!cell.isMine){
		if (cell.near > 0)
			str[1] = (char)(48 + cell.near);
		else
			str[1] = ' ';
		char* strp = str;
		printf(strp);
		return;
	}

	char* strp = str;
	printf(strp); return;
}


void printInfo(char* info, int y){
	printf("\x1b[%d;%dH", y + 1, (COL * 4) + 4);
	printf(info);
	printf("\x1b[%d;1H", ROW * 2 + 2);
}


void drawInfoGrid(int dataLines, int maxDataLen){
	printf("\x1b[%d;%dH", 1, (COL * 4) + 3);

	printf("╭");
	for (int x=0; x<maxDataLen; x++){
		printf("─");
	}
	printf("╮");
	
	for (int y=0; y<dataLines; y++){
		printf("\x1b[%d;%dH", y + 2, (COL * 4) + 3);
		printf("│");
		for (int x=0; x<maxDataLen; x++){
			printf(" ");
		}
		printf("│");
	}
	
	printf("\x1b[%d;%dH", dataLines + 2, (COL * 4) + 3);

	printf("╰");
	for (int x=0; x<maxDataLen; x++){
		printf("─");
	}
	printf("╯");
	
	printf("\x1b[%d;1H\r", 2 * ROW + 2);
}


void drawGrid(bool enoughSize){
	printf("╭");
	for (int x=0; x<COL - 1; x++)
		printf("───┬");
	printf("───╮\n\r");
	
	for (int y=0; y<ROW; y++){
		for(int x=0; x<COL; x++){
			printf("│   ");
		}
		printf("│\n\r");
		
		if (y + 1 < ROW){
			printf("├");
			for (int x=0; x<COL - 1; x++){
				printf("───┼");
			}
			printf("───┤\n\r");
		}
	}

	printf("╰");
	for (int x=0; x<COL - 1; x++){
		printf("───┴");
	}
	printf("───╯\n\r");

	if (!enoughSize)
		return;

	drawInfoGrid(4, 9);

}


void drawFull(struct Cell map[ROW][COL]){
	printf("\x1b[H\x1b[2J");  // Clear screen
	drawGrid(true);
	
	for (int y=0; y<ROW; y++){
		for (int x=0; x<COL; x++){
			setPos(x, y);
			printf("\x1b[0m");
			printf(getColor(map[y][x]));
			printString(map[y][x]);
			// printf("\x1b[%d;1H\r", (2 + 2 * ROW));
		}
	}
	printf("\x1b[%d;1H\n\r", (2 + 2 * ROW));
}


void draw(struct Cell map[ROW][COL], struct Cell lmap[ROW][COL]){
	for (int y=0; y<ROW; y++){
		for (int x=0; x<COL; x++){
			if (
				map[y][x].isOpen != lmap[y][x].isOpen ||
				map[y][x].isFlag != lmap[y][x].isOpen ||
				(cursor[0] == x && cursor[1] == y) ||
				(lcursor[0] == x && lcursor[1] == y)
				){
				
				setPos(x, y);
				printf("\x1b[0m");
				printf(getColor(map[y][x]));
				printString(map[y][x]);
			}
		}
	}
	printf("\x1b[0m\x1b[%d;1H\n\r", (2 + 2 * ROW));
}


void genWorld(struct Cell map[ROW][COL],
				struct Cell lmap[ROW][COL]){
	for (int y=0; y<ROW; y++){
		for (int x=0; x<COL; x++){
			struct Cell c = {false,
			false,
			false,
			0,
			x, y};

			map[y][x] = c;
			lmap[y][x] = c;
		}
	}
}


#endif // MAP_H

