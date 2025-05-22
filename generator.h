#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdlib.h>

static char *buff = NULL;
char generate_letter();
char *generate_text();
void alloc_buffer();

char generate_letter() {
	return all_chars[rand() % (sizeof(all_chars) - 1)];
}

char *generate_text() {
	unsigned int i, j;
	char *s;

	alloc_buffer();
	s = buff;
	for(i = 0; i < gen_length; ++i) {
		for(j = 0; j < word_length; ++i) {
			*s = generate_letter();
			++s;
		}
		*s = ' ';
		++s;
	}
	*s = '\0';
	return buff;
}

void alloc_buffer() {
	if(buff) free (buff);
	buff = (char *)malloc(1 + gen_length * (word_length + 1));
}

#endif

