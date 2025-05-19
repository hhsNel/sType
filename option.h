struct option_value {
	int *b;
	char *s;
	unsigned int *u;
};

struct option {
	char *dsp_string;
	struct option_value value;
};

