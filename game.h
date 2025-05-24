#ifndef GAME_H
#define GAME_H

#include "generator.h"
#include "progress.h"
#include "progressmenu.h"

#include <time.h>
#include <string.h>

static char *current_text;
static char *typed_text;
#define TYPED_LENGTH (typed_text-current_text)
static unsigned int mistakes[PROGRESS_PTS];
static struct timespec start_time;

unsigned int total_mistakes();
void insert_mistake();
void display_stats();
void display_text();
void start_game();
void update_progress();
struct timespec diff_time(struct timespec start, struct timespec end);

unsigned int total_mistakes() {
	unsigned int i, total = 0;

	for(i = 0; i < PROGRESS_PTS; ++i) {
		total += mistakes[i];
	}
	return total;
}

void insert_mistake() {
	mistakes[PROGRESS_PTS * TYPED_LENGTH / (gen_length * (word_length + 1))] += 1;
}

void display_stats() {
	struct timespec now;

	clock_gettime(CLOCK_MONOTONIC, &now);
#define BILLION 1000000000ULL
#define DIFF diff_time(start_time, now)
	printf("\033[2J\033[H" CLR_TIME "TIME: %us %uns" TXT_RESET "\n" CLR_CHARS "CHARACTERS: %u" TXT_RESET "\n" CLR_WPM "WPM: %f" TXT_RESET "\n" CLR_MISTAKES "TOTAL MISTAKES: %u" TXT_RESET "\n",
	                                       DIFF.tv_sec, DIFF.tv_nsec,                      TYPED_LENGTH,                    (double)(TYPED_LENGTH*12ULL*BILLION)/(double)(DIFF.tv_sec*BILLION+DIFF.tv_nsec),
	                                                                                                                                                                         total_mistakes());
#undef BILLION
#undef DIFF
}

void display_text() {
	unsigned int index = TYPED_LENGTH, word_start = (index / (word_length + 1)) * (word_length + 1), cursor_in_word = index % (word_length + 1);

	if(word_start > 0) {
		printf(CLR_TEXT "%.*s" TXT_RESET, word_start, current_text);
	}
	if(cursor_in_word > 0) {
		printf(CLR_WORD "%.*s" TXT_RESET, cursor_in_word, current_text + word_start);
	}
	printf(CLR_CURRENT "%c" TXT_RESET, current_text[index]);
	if(cursor_in_word < word_length) {
		printf(CLR_WORD "%.*s" TXT_RESET, word_length - cursor_in_word, typed_text + 1);
	}
	if(word_start + word_length + 1 < gen_length * (word_length + 1) - 1) {
		printf(CLR_TEXT "%s" TXT_RESET, current_text + word_start + word_length + 1);
	}
	printf("\n\n");
}

void start_game() {
	struct timespec now;
	unsigned int i;
	char c;
	struct progress p;

	current_text = generate_text();
	typed_text = current_text;
	for(i = 0; i < PROGRESS_PTS; ++i) {
		mistakes[i] = 0;
	}
	clock_gettime(CLOCK_MONOTONIC, &start_time);

	enter_immediate();
	while(typed_text < current_text + gen_length * (word_length + 1)) {
		display_stats();
		display_text();
		scanf("%c", &c);
		if(c == *typed_text) {
			++typed_text;
		} else {
			insert_mistake();
		}
	}
	enter_normal();
	clock_gettime(CLOCK_MONOTONIC, &now);
	for(i = 0; i < PROGRESS_PTS; ++i) {
		global_progress.mistake_pts[i] += mistakes[i];
	}
	global_progress.total_chars += gen_length * (word_length + 1);
	global_progress.total_time += diff_time(start_time, now).tv_sec * 1000000000ULL + diff_time(start_time, now).tv_nsec;
	if(save_progress) {
		save_global_progress();
	}

	p.total_chars = gen_length * (word_length + 1);
	p.total_time = diff_time(start_time, now).tv_sec * 1000000000ULL + diff_time(start_time, now).tv_sec;
	for(i = 0; i < PROGRESS_PTS; ++i) {
		p.mistake_pts[i] = mistakes[i];
	}
	render_progress(p);
}

struct timespec diff_time(struct timespec start, struct timespec end) {
	struct timespec diff;
	
	if (end.tv_nsec < start.tv_nsec) {
		diff.tv_sec = end.tv_sec - start.tv_sec - 1;
		diff.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	} else {
		diff.tv_sec = end.tv_sec - start.tv_sec;
		diff.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	
	return diff;
}

#endif

