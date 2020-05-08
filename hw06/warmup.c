 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>

char* my_strdup(const char* original) {
	
	// Finds size of original string
	int num_of_chars = 0;
	do {
		num_of_chars++;
	} while (*original++ != '\0');  
	original -= num_of_chars;

	// Copies value of original into new string
	char* malloc_string = malloc(sizeof(*original) * num_of_chars);
	for (int character = 0; character < num_of_chars; character++) {
		malloc_string[character] = original[character];
	}
	
	return malloc_string;
}

int main(int argc, char *argv[]) {
	char s[] = "abc\n";
	fputs(s, stdout);  // Should print "abc" followed by a newline ('\n')

	char* t = my_strdup(s);
	fputs(t, stdout);  // Should print "abc" followed by a newline ('\n')
	free(t);

	return EXIT_SUCCESS;
}
