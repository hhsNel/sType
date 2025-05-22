#ifndef MAINMENU_H
#define MAINMENU_H

#include <stdio.h>

#include "optionmenu.h"

#define MENU_LENGTH (sizeof(menu_keys)/sizeof(menu_keys[0]))

void render_menu();
void summarize_keybind(struct key k);
int handle_menu_input();

void render_menu() {
	unsigned int i;

        printf("\033[?25l");

        do {
                printf("\033[2J\033[H%s\n", menu_str);

                for(i = 0; i < MENU_LENGTH; ++i) {
			summarize_keybind(menu_keys[i]);
                }
        } while(handle_menu_input());

        printf("\033[?25h");
        enter_normal();
}

#endif

