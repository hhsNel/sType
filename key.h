#ifndef KEY_H
#define KEY_H

struct key {
	char trigger;
	void (*func)();
};

#endif

