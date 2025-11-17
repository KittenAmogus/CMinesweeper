#ifndef GAME_H
#define GAME_H


int cursor[2] = {0, 0};
int lcursor[2] = {0, 0};


void moveCursor(int moveOn[2]){
	if (cursor[0] + moveOn[0] >= COL || cursor[1] + moveOn[1] >= ROW)
		return;
	if ((moveOn[0] + cursor[0]) < 0 || (moveOn[1] + cursor[1]) < 0)
		return;

	lcursor[0] = cursor[0];
	lcursor[1] = cursor[1];
	cursor[0] += moveOn[0];
	cursor[1] += moveOn[1];
}


#endif // GAME_H
