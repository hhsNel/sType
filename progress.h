#ifndef PROGRESS_H
#define PROGRESS_H

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PROGRESS_PTS 32
#define PROGRESS_PATH_LEN 512
struct progress {
	unsigned long int mistake_pts[PROGRESS_PTS];
	unsigned long long int total_chars;
	unsigned long long int total_time;
};

struct progress global_progress;

void load_global_progress();
void save_global_progress();

void load_global_progress() {
	char path_buff[PROGRESS_PATH_LEN], *xdg_data, *home;
	FILE *f;

	xdg_data = getenv("XDG_DATA_HOME");
	home = getenv("HOME");

	if(xdg_data) {
		snprintf(path_buff, PROGRESS_PATH_LEN, "%s/sType", xdg_data);
	} else {
		if(home) {
			snprintf(path_buff, PROGRESS_PATH_LEN, "%s/.local/share/sType", home);
		} else {
			path_buff[0] = '.';
			path_buff[1] = '\0';
		}
	}

	mkdir(path_buff, 0755);
	
	strncat(path_buff, "/", PROGRESS_PATH_LEN-strlen(path_buff)-1);
	strncat(path_buff, progress_file, PROGRESS_PATH_LEN-strlen(path_buff)-1);
	f = fopen(path_buff, "rb");
	if(!f) {
		enter_immediate();
		printf("Could not open progress file at: %s ; initialized with zeros\nPress any key to continue\n", path_buff);
		getchar();
		enter_normal();
	} else {
		fread(&global_progress, sizeof(struct progress), 1, f);
		fclose(f);
	}
}

void save_global_progress() {
	char path_buff[PROGRESS_PATH_LEN], *xdg_data, *home;
	FILE *f;

	xdg_data = getenv("XDG_DATA_HOME");
	home = getenv("HOME");

	if(xdg_data) {
		snprintf(path_buff, PROGRESS_PATH_LEN, "%s/sType/%s", xdg_data, progress_file);
	} else {
		if(home) {
			snprintf(path_buff, PROGRESS_PATH_LEN, "%s/.local/share/sType/%s", home, progress_file);
		} else {
			snprintf(path_buff, PROGRESS_PATH_LEN, "./%s", progress_file);
		}
	}
	
	f = fopen(path_buff, "wb");
	if(!f) {
		enter_immediate();
		printf("Could not open progress file at: %s ; discarding instead of saving\nPress any key to continue\n", path_buff);
		getchar();
		enter_normal();
	} else {
		fwrite(&global_progress, sizeof(struct progress), 1, f);
		fclose(f);
	}
}

#endif

