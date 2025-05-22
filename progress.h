#ifndef PROGRESS_H
#define PROGRESS_H

#define PROGRESS_PTS 32
struct progress {
	unsigned long int mistake_pts[PROGRESS_PTS];
	unsigned long long int total_time;
};

struct progress global_progress;

#endif

