#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include "frequencies.h"
#include "miniunit.h"

int _test_valid_file() {
	mu_start();

	Frequencies freqs = {0};
	const char** a_error = malloc(sizeof(char**));
	*a_error = NULL;
	bool is_valid = calc_frequencies(freqs, "gophers", a_error);
	mu_check(is_valid);
	mu_check((*a_error == NULL));
	mu_check((freqs['g'] == 3));
	mu_check((freqs['o'] == 3));
	mu_check((freqs[' '] == 2));

	mu_end();
}

int _test_invalid_file() {
	mu_start();

	Frequencies freqs = {0};
	const char** a_error = malloc(sizeof(char**));
	*a_error = NULL;
	bool is_valid = calc_frequencies(freqs, "~/264/hw12/fake_file.txt", a_error);
	mu_check(!is_valid);
	mu_check((*a_error == strerror(errno)));

	mu_end();
}


int main(int argc, char* argv[]) {

	mu_run(_test_valid_file);
	mu_run(_test_invalid_file);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
