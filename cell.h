#ifndef CELL_H
#define CELL_H


struct Cell{
	bool isOpen;
	bool isFlag;
	bool isMine;
	int near;

	int x;
	int y;
};


#endif // CELL_H

