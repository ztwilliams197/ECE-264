#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "hw02.h"

int main(int argc, char* argv[]) {
	
	print_integer(    513, 14,   "");
	printf("\n");

	print_integer(  -188, 16, "0x");
	printf("\n");

	print_integer(INT_MAX, 36,   "");
	printf("\n");

	print_integer(INT_MIN,  8,  "0");
	printf("\n");

	print_integer(     64,  8,  "$");
	printf("\n");
	
	print_integer(INT_MIN, 36, "XX");
	printf("\n");

	print_integer(      0,  2,  "$");

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
