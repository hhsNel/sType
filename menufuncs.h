#ifndef MENUFUNCS_H
#define MENUFUNCS_H

#include "stdlib.h"
#include "stdio.h"

void quit();
void render_options();
void start_game();
void manual_save();
void view_progress();

void quit() {
	printf("\033[?25h");
	enter_normal();
	exit(0);
}

void manual_save() {
	printf("NOT IMPLEMENTED\n");
	exit(1);
}
void view_progress() {
	printf("NOT IMPLEMENTED\n");
	exit(1);
}

#endif

