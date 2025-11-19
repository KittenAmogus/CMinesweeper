#include <stdio.h>
#include "term_states.h"
#include "settings.h"
#include "game.h"
#include "cell.h"
#include "map.h"


int main(void){
	struct Cell world[ROW][COL];
	struct Cell lworld[ROW][COL];
	setRawMode();

	genWorld(world, lworld);
	drawFull(world);

	while (true){
		int move2[2] = {0, 0};
		char c = getChar();
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
				int repeats = 0;
				while (!genMines(world) && repeats++ < 4){
					for (int x=0; x<COL; x++){
						for (int y=0; y<ROW; y++){
							world[y][x].isMine = false;
						}
					}
				};

				if (repeats >= 4){
					setNormalMode();
					printf("\x1b[0mError mines generation!\n\r");
					printf("Maybe [%d] is too big\n\r", MINES);
					return 1;
				}

				genNear(world);
				
				if (revealCell(world, &world[cursor[1]][cursor[0]])){
					drawFull(world);
					gameOverFunc(world);
					setNormalMode();
					return 0;
				}
				
				break;
			case '\r':
				world[cursor[1]][cursor[0]].isFlag = (
					!world[cursor[1]][cursor[0]].isFlag
				);
				break;

			default:
				continue;
		}
		moveCursor(move2, world);
		draw(world, lworld);
		
		if (!gameOver)
			break;
	}
	

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
				if (revealCell(world, &world[cursor[1]][cursor[0]])){
					gameOver = true;
					gameOverFunc(world);
					draw(world, lworld);
					setNormalMode();
					return 0;
				}
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

