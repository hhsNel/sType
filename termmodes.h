#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>

static struct termios term;

void init_term() {
	tcgetattr(STDIN_FILENO, &term);
}

void enter_immediate() {
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void enter_normal() {
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

