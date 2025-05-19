#include "termmodes.h"
#include "color.h"
#include "option.h"
#include "optionmenu.h"

int main(int argc, char **argv) {
	init_term();
	render_options();
	return 0;
}

