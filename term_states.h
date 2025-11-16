#include <unistd.h>
#include <termios.h>

#ifndef TERM_STATES_H
#define TERM_STATES_H

struct termios term;

void setRawMode(void){
	tcgetattr(STDOUT_FILENO, &term);
	struct termios raw = term;
	cfmakeraw(&raw);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void setNormalMode(void){
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &term);
}

char getChar(void){
	char c;
	read(STDIN_FILENO, &c, 1);
	return c;
}

#endif // TERM_STATES_H

