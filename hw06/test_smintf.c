#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smintf.h"
#include "miniunit.h"
#include "clog.h"

#define mu_check_smintf(expected, ...) \
	do { \
		char* actual = smintf(__VA_ARGS__); \
		mu_check_strings_eq((expected), (actual)); \
		free(actual);\
	} while(0)

int _test_empty() {
	mu_start();

	mu_check_smintf("", parse_int, );

	mu_end();
}

int _test_format_only() {
	mu_start();

	mu_check_smintf("Test only format string", "Test only format string");
	mu_check_smintf("Test only format string", "Test only format string");
	mu_check_smintf("This has no variables", "This has no variables");

	mu_end();
}

int _test_string_var() {
	mu_start();

	mu_check_smintf("This is a string variable", "%s", "This is a string variable");
	mu_check_smintf("This contains a string", "This contains a %s", "string");

	mu_end();
}

int _test_int_var() {
	mu_start();

	mu_check_smintf("10000", "%d", 10000);
	mu_check_smintf("0x1", "%x", 16);
	mu_end();
}

int _test_double_var() {
	mu_start();

	mu_check_smintf("$1234.67", "%$", 1234.67);

	mu_end();
}

int main(int argc, char* argv[]) {

	mu_run(_test_empty);
	mu_run(_test_format_only);
	mu_run(_test_int_var);
	mu_run(_test_string_var);
	mu_run(_test_double_var);

	return EXIT_SUCCESS;
}
