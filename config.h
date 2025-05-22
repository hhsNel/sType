/* time color */
#define CLR_TIME BG_RGB(256,256,256) FG_RGB(255,255,255) TXT_BOLD
/* chars # color */
#define CLR_CHARS BG_256(127) FG_256(63) TXT_BOLD
/* wpm color */
#define CLR_WPM BG_USR(2) FG_USR(6) TXT_BLINKING
/* mistakes color */
#define CLR_MISTAKES BG_USR(7) FG_USR(0)
/* letter color */
#define CLR_CURRENT BG_USR(5) TXT_BOLD
/* word color */
#define CLR_WORD BG_USR(3)
/* text color */
#define CLR_TEXT 

char all_chars[256] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";	/* 4x as likely to choose a lowercase than an uppercase */

int repeat_mistakes = 1; /* repeat letters leading up to a mistake */
/* how many mistakes to remember, and their length */
char mistake_buffer[4][4];

/* auto-save progress */
int save_progress = 1;
/* file in which progress is saved */
char progress_file[256] = ".sType-progress";

/* menu controls */
struct key menu_keys[] = {
/*	 key	function */
	{'q',	quit},
	{':',	render_options},
	{'i',	start_game},
	{'w',	manual_save},
	{'p',	view_progress},
};
char menu_str[256] = "WELCOME TO sType BY NEL!\nYOU CAN FIND THE SOURCE AT https://github.com/hhsNel/sType\nCURRENT VERSION: 0.0.2\n";

/* use metronome during typing */
int use_metronome = 0;
/* metronome delay in microseconds */
unsigned int metronome_delay = 500000;

/* character groups */
unsigned int word_length = 5;
/* text length */
unsigned int gen_length = 20;

struct option options[] = {
/*	 text			setting */
	{"character list",      {.s=all_chars}},
	{"repeat mistakes",     {.b=&repeat_mistakes}},
	{"autosave",            {.b=&save_progress}},
	{"metronome ?",	        {.b=&use_metronome}},
	{"metronome delay",     {.u=&metronome_delay}},
	{"word len",            {.u=&word_length}},
	{"text len",            {.u=&gen_length}},
	{"main menu string",    {.s=menu_str}},
};

