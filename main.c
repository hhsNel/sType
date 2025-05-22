#include "color.h"
#include "option.h"
#include "key.h"
#include "config.h"
#include "termmodes.h"
#include "mainmenu.h"

int main(int argc, char **argv) {
	init_term();
	render_options();
	return 0;
}

