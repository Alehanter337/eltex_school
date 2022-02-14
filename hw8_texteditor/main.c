#include "main.h"
#include <asm-generic/ioctls.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>


void sig_winch(int signo)
{
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}

void text_edit(){
	int key = wgetch(stdscr);
	int row = 0;
	int col = 0;
	getyx(stdscr, row, col);

	switch (key) {
		case KEY_LEFT:
			move(row, col - 1);
			break;

		case KEY_UP:
			move(row - 1, col);

		case KEY_BACKSPACE:
			getyx(stdscr, row, col);
			mvwaddch(stdscr, row, col, ' ');
			refresh();
			move(row, col);
			break;
	}
}
	



int main(int argc, char ** argv)
{
	initscr();
	savetty();
	curs_set(0);
	keypad(stdscr, TRUE);
	refresh();
	getch();
	while(1) {
		text_edit();
		refresh();
	}
	finish();
	return 0;
}
