#ifndef MENUFUNCS_H
#define MENUFUNCS_H

#include "stdlib.h"
#include "stdio.h"

void quit();
void render_options();
void start_game();
void save_global_progress();
void render_progress_menu();

void quit() {
	printf("\033[?25h");
	enter_normal();
	exit(0);
}

#endif

