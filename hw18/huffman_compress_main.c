// © 2020  Alexander J Quinn 2020.  All Rights Reserved.
//         This content is protected and may not be shared, uploaded, or distributed.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "huffman_compress.h"


int main(int argc, const char* argv[]) {
	const char* error = check_command_line_arguments(argc, argv);

	if(*error != '\0') {
		const char* in_path = argv[1];
		const char* out_path = argv[2];

		compress_file(in_path, out_path);
	} else {
		printf(error);
	}

	return EXIT_SUCCESS;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
