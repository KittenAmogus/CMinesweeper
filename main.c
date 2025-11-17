#include <stdio.h>
#include "term_states.h"
#include "settings.h"
#include "game.h"
#include "cell.h"
#include "map.h"


int main(void){
	struct Cell world[ROW][COL];
	struct Cell lworld[ROW][COL];

	genMap(world, lworld);

	for (int x=0; x<COL; x++){
		world[0][x].near = x;
	}
	world[1][1].isFlag = true;
	world[1][2].isMine = true;
	world[1][3].isMine = true;

	setRawMode();
	
	draw_one(world);

	while (true){
		char c = getChar();
		int move2[2] = {0, 0};
		switch (c){
			case 'a':
				move2[0]--;
				break;
			case 'd':
				move2[0]++;
				break;
			case 'w':
				move2[1]--;
				break;
			case 's':
				move2[1]++;
				break;
			case ' ':
				world[cursor[1]][cursor[0]].isOpen = true;
				break;
			default:
				draw_one(world);
				setNormalMode();
				return 0;
		}
		moveCursor(move2);
		draw(world, lworld);
	}

	setNormalMode();
	return 0;
}

