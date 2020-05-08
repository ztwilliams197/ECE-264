#ifndef __MINIUNIT_H__
#define __MINIUNIT_H__
#include "clog.h"

#define mu_start() int __mu_line_num_first_error = 0

#define mu_check(condition) {\
	if((condition == 0) && (__mu_line_num_first_error == 0)) {\
		__mu_line_num_first_error = __LINE__;\
	}\
}

#define mu_run(function) {\
	int __mu_line_number = function();\
	if(__mu_line_number == 0) {\
		fprintf(stderr, ANSI_GREEN "Test passed: %s" ANSI_RESET "\n", (#function));\
	}\
	else {\
		fprintf(stderr, ANSI_RED "Test failed: %s at line %d" ANSI_RESET "\n", (#function), (__mu_line_number));\
	}\
}

#define mu_end() return __mu_line_num_first_error

#endif
