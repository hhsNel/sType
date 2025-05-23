#ifndef PROGRESSMENU_H
#define PROGRESSMENU_H

#include <stdio.h>

#include "progress.h"

void render_progress_menu();
void render_progress(struct progress p);
unsigned int max_mistake_bar_height(struct progress p);

void render_progress_menu() {
	render_progress(global_progress);
}

void render_progress(struct progress p) {
	unsigned int i, j, scale, bars[PROGRESS_PTS];

	scale = 1 + max_mistake_bar_height(p)/PROGRESS_BAR_MAX_HEIGHT;
	for(i = 0; i < PROGRESS_PTS; ++i) {
		bars[i] = p.mistake_pts[i] / scale;
	}

	for(i = 0; i < PROGRESS_BAR_MAX_HEIGHT; ++i) {
		for(j = 0; j < PROGRESS_PTS; ++i) {
			if(bars[j] == i) {
				printf("%s", MISTAKE_EQ);
			} else {
				if(bars[j] > i) {
					printf("%s", MISTAKE_GT);
				} else {
					printf(" ");
				}
			}
		}
		printf("\n");
	}
	printf("TOTAL CHARS: %llu\nTOTAL NS: %llu\nAVG WPM: %f\nPress any key to proceed\n", p.total_chars, p.total_time, (double)(p.total_chars * 200000000ULL)/(double)(p.total_time));
	enter_immediate();
	getchar();
	enter_normal();
}

unsigned int max_mistake_bar_height(struct progress p) {
	unsigned int i, max = p.mistake_pts[0];

	for(i = 1; i < PROGRESS_PTS; ++i) {
		if(p.mistake_pts[i] > max) {
			max = p.mistake_pts[i];
		}
	}
	return max;
}

#endif

