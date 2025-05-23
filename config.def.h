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
/* text to display as the first "pixel" of the mistake graph */
#define MISTAKE_EQ FG_USR(7) TXT_BOLD "X" TXT_RESET
/* text to display below the first "pixel" */
#define MISTAKE_GT FG_USR(7) "|" TXT_RESET

char all_chars[256] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";	/* 4x as likely to choose a lowercase than an uppercase */

int repeat_mistakes = 1; /* repeat letters leading up to a mistake */
/* how many mistakes to remember, and their length */
char mistake_buffer[4][4];

/* auto-save progress */
int save_progress = 1;
/* file in which progress is saved */
char progress_file[256] = "progress";

/* fallback to recover terminal state when menu_keys or quit broken */
#define USE_UNIVERSAL_QUIT 0

/* menu controls */
struct key menu_keys[] = {
/*	 key	function */
	{'q',	quit},
	{':',	render_options},
	{'i',	start_game},
	{'w',	save_global_progress},
	{'p',	render_progress_menu},
};
char menu_str[256] = "WELCOME TO sType BY NEL!\nYOU CAN FIND THE SOURCE AT https://github.com/hhsNel/sType\nCURRENT VERSION: 1.0.4\n";

/* character groups */
unsigned int word_length = 5;
/* text length */
unsigned int gen_length = 32;

struct option options[] = {
/*	 text                   setting */
	{"character list",      {.s=all_chars}},
	{"repeat mistakes",     {.b=&repeat_mistakes}},
	{"autosave",            {.b=&save_progress}},
	{"word len",            {.u=&word_length}},
	{"text len",            {.u=&gen_length}},
	{"main menu string",    {.s=menu_str}},
};

#define PROGRESS_PTS 32
#define PROGRESS_BAR_MAX_HEIGHT 32

