#include <stdio.h>
#include "term_states.h"
#include "settings.h"
#include "game.h"
#include "cell.h"
#include "map.h"


int main(void){
	struct Cell world[ROW][COL];
	struct Cell lworld[ROW][COL];
	
	genWorld(world, lworld);
	setRawMode();

	drawFull(world);
	while (true){	
		char c = getChar();
		int move2[2] = {0, 0};
		switch (c){

			case 3:
				setNormalMode();
				return 0;

			case 'w':
				move2[1]--;
				break;
			case 's':
				move2[1]++;
				break;
			case 'd':
				move2[0]++;
				break;
			case 'a':
				move2[0]--;
				break;
	
			case ' ':
				revealCell(world, & world[cursor[1]][cursor[0]]);
				break;
			case '\r':
				world[cursor[1]][cursor[0]].isFlag = (
					!world[cursor[1]][cursor[0]].isFlag
				);
				break;
		}
		moveCursor(move2, world);
		draw(world, lworld);
		// draw(world, lworld);
	}
	
	setNormalMode();
	return 0;
}

