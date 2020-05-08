#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include "frequencies.h"

bool calc_frequencies(Frequencies freqs, const char* path, const char** a_error) {
	bool valid_file = true;

	// Attempt to open file
	FILE* input_file = fopen(path, "r");

	// If file path is valid, change to valid char freqs
	if(input_file != NULL) {
		for(uchar curr_char = fgetc(input_file); !feof(input_file); curr_char = fgetc(input_file)) {
			freqs[curr_char] += 1;
		}
	} else { // If file path is invalid, change valid_file and a_error
		valid_file = false;
		*a_error = strerror(errno);
	}

	return valid_file;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
