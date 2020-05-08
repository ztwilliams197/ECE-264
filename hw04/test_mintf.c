#include <stdio.h>
#include <stdlib.h>
#include "mintf.h"

int main(int argc, char* argv[]) {
	mintf("Format %% string test%"); // Gives weird number output after %
	printf("\n");

	mintf("%d", 25);
	printf("\n");

	mintf("%x", 25);
	printf("\n");
	
	mintf("%b", 25);
	printf("\n");

	mintf("%$", 25.75);
	printf("\n");

	mintf("%s", "Testing string variable");
	printf("\n");

	mintf("%c", 'W'); // Gives weird char output
	printf("\n");

	mintf("Testing integrated int %d", 25);
	printf("\n");

	mintf("Testing integrated hex %x", 25);
	printf("\n");
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
