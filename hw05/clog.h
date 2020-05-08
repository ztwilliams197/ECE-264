#ifndef __CLOG_H__
#define __CLOG_H__

#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN "\x1b[36m"
#define ANSI_RESET "\x1b[0m"

#ifdef DEBUG
#	define log_msg(msg) fprintf(stderr, "%s", (msg)) // Enabled
#else
#	define log_msg(msg)								 // Disabled
#endif

#ifdef DEBUG
#	define log_int(n) fprintf(stderr, "%s == %d\n",(#n), (n))   // Enabled
#else
#	define log_int(n) fprintf(stderr, "%d\n", (n))	   // Disabled
#endif

#ifdef DEBUG
#	define log_str(s) fprintf(stderr, "%s == %s\n",(#s), (s))   // Enabled
#else
#	define log_str(s)								 // Disabled
#endif

#ifdef DEBUG
#	define log_char(c) fprintf(stderr, "%s == %c\n", (#c), (c))  // Enabled
#else
#	define log_char(c)								 // Disabled
#endif

#ifdef DEBUG
#	define log_addr(addr) fprintf(stderr, "%s == %p\n", (#addr), (addr)) // Enabled
#else
#	define log_addr(addr)								 // Disabled
#endif

#ifdef DEBUG
#	define log_red(...){\
	fprintf(stderr, ANSI_RED);\
	fprintf(stderr, __VA_ARGS__);\
	fprintf(stderr, ANSI_RESET);\
}
#else
#	define log_red(...)								 // Disabled
#endif

#ifdef DEBUG
#	define log_green(...){\
	fprintf(stderr, ANSI_GREEN);\
	fprintf(stderr, __VA_ARGS__);\
	fprintf(stderr, ANSI_RESET);\
}
#else
#	define log_green(...)								 // Disabled
#endif

#ifdef DEBUG
#	define log_yellow(...){\
	fprintf(stderr, ANSI_YELLOW);\
	fprintf(stderr, __VA_ARGS__);\
	fprintf(stderr, ANSI_RESET);\
}
#else
#	define log_yellow(...)								 // Disabled
#endif

#ifdef DEBUG
#	define log_blue(...){\
	fprintf(stderr, ANSI_BLUE);\
	fprintf(stderr, __VA_ARGS__);\
	fprintf(stderr, ANSI_RESET);\
}
#else
#	define log_blue(...)								 // Disabled
#endif

#ifdef DEBUG
#	define log_magenta(...){\
	fprintf(stderr, ANSI_MAGENTA);\
	fprintf(stderr, __VA_ARGS__);\
	fprintf(stderr, ANSI_RESET);\
}
#else
#	define log_magenta(...)								 // Disabled
#endif

#ifdef DEBUG
#	define log_cyan(...){\
	fprintf(stderr, ANSI_CYAN);\
	fprintf(stderr, __VA_ARGS__);\
	fprintf(stderr, ANSI_RESET);\
}
#else
#	define log_cyan(...)								 // Disabled
#endif

#endif
