#ifndef MAINMENU_H
#define MAINMENU_H

#include <stdio.h>

#include "optionmenu.h"
#include "generator.h"

#define MENU_LENGTH (sizeof(menu_keys)/sizeof(menu_keys[0]))

void render_menu();
void summarize_keybind(struct key k);
int handle_menu_input();

void render_menu() {
	unsigned int i;

        do {
                printf("\033[2J\033[H%s\n", menu_str);

                for(i = 0; i < MENU_LENGTH; ++i) {
			summarize_keybind(menu_keys[i]);
                }
        } while(handle_menu_input());

        printf("\033[?25h");
        enter_normal();
}

void summarize_keybind(struct key k) {
	printf("%c\t|\t%p\n", k.trigger, (void *)k.func);
}

int handle_menu_input() {
	char c;
	unsigned int i;

	enter_immediate();
        printf("\033[?25l");
	scanf("%c", &c);

	if((unsigned char)c == 27) {
		printf("Universal quit\n");
		return 0;
	}

	for(i = 0; i < MENU_LENGTH; ++i) {
		if(c == menu_keys[i].trigger) {
			menu_keys[i].func();
		}
	}
	return 1;
}

#endif

