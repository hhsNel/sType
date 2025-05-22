#include "color.h"
#include "option.h"
#include "key.h"
#include "termmodes.h"
#include "menufuncs.h"
#include "config.h"
#include "mainmenu.h"

#include <stdlib.h>

int main(int argc, char **argv) {
	init_term();
	srand(time(0));

	render_menu();
	return 0;
}

