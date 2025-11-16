#include <stdio.h>
#include "term_states.h"
#include "settings.h"
#include "cell.h"
#include "map.h"


int main(void){
	struct Cell world[ROW][COL];
	struct Cell lworld[ROW][COL];
	genMap(world, lworld);

	for (int x=0; x<COL; x++){
		world[0][x].near = x;
		world[0][x].isOpen = true;
	}
	world[1][1].isFlag = true;
	world[1][2].isMine = true;
	world[1][2].isOpen = true;

	setRawMode();
	
	draw_one(world);

	setNormalMode();
	return 0;
}

