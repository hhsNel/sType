#include <stdio.h>

#include "config.h"

#define OPTIONS_LENGTH (sizeof(options)/sizeof(struct option))

static unsigned int chosen_option;
void render_options();
int handle_option_input();
void render_option(struct option o, unsigned int offset, int is_chosen);
void calculate_offset(struct option o);

void render_options() {
	unsigned int i, max_offset = 0, current_offset;

	chosen_option = 0;
	
	for(i = 0; i < OPTIONS_LENGH; ++i) {
		current_offset = calculate_offset(options[i]);
		if(current_offset > max_offset) max_offset = current_offset;
	}

	do {
		printf("ANSI escape for clear terminal");
		for(i = 0; i < OPTIONS_LENGH; ++i) {
			render_option(options[i], max_offset, i == chosen_option);
		}
	} while(handle_option_input());
}

