#include "color.h"
#include "option.h"
#include "key.h"
#include "termmodes.h"
#include "menufuncs.h"
#include "config.h"
#include "mainmenu.h"

int main(int argc, char **argv) {
	init_term();
	render_menu();
	return 0;
}

