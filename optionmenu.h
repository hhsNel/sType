#include <stdio.h>
#include <string.h>

#include "config.h"

#define OPTIONS_LENGTH (sizeof(options)/sizeof(struct option))

static unsigned int chosen_option;
void render_options();
int handle_option_input();
void render_option(struct option o, unsigned int offset, int is_chosen);
unsigned int calculate_offset(struct option o);
void handle_edit_option(struct option o);

void render_options() {
	unsigned int i, max_offset = 0, current_offset;

	chosen_option = 0;
	
	for(i = 0; i < OPTIONS_LENGTH; ++i) {
		current_offset = calculate_offset(options[i]);
		if(current_offset > max_offset) max_offset = current_offset;
	}

	do {
		printf("\033[2J\033[H");
		for(i = 0; i < OPTIONS_LENGTH; ++i) {
			render_option(options[i], max_offset, i == chosen_option);
		}
	} while(handle_option_input());
}

int handle_option_input() {
	char c;

	enter_immediate();
	scanf("%c", &c);
	switch(c) {
		case 'q':
			return 0;
		case 'j':
			++chosen_option;
			chosen_option %= OPTIONS_LENGTH;
			break;
		case 'k':
			chosen_option += (OPTIONS_LENGTH - 1);
			chosen_option %= OPTIONS_LENGTH;
			break;
		case '\n':
			handle_edit_option(options[chosen_option]);
			break;
	}
	return 1;
}

void render_option(struct option o, unsigned int offset, int is_chosen) {
	printf("%*s\t|\t%c\t|\t", offset, o.dsp_string, is_chosen ? '*' : '_');
	if(o.value.u != NULL) {
		printf("UNSIGNED INT\t|\t%u\n", *o.value.u);
		return;
	}
	if(o.value.s != NULL) {
		printf("STRING     \t|\t%s\n", *o.value.s);
		return;
	}
	printf("BOOLEAN     \t|\t%c\n", (*o.value.b) ? 'T' : 'F');
}

unsigned int calculate_offset(struct option o) {
	return strlen(o.dsp_string);
}

void handle_edit_option(struct option o) {
	char c;

	enter_normal();
	printf("\n\n");
	while(1) {
		printf("\033[27mEDIT OPTION: \033[7m");
		if(o.value.u != NULL && !scanf("%u", o.value.u)) {
			return;
		}
		if(o.value.s != NULL && !scanf("%s", *o.value.s)) {
			return;
		}
		if(!scanf("%c", &c) && (c == 't' || c == 'T' || c == 'f' || c == 'F')) {
			*o.value.b = c == 't' || c == 'T';
			return;
		}
	};
}

