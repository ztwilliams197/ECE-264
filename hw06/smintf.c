/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#ifndef __smintf_h__
#define __smintf_h__
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

char _add_char(char* full_string, char new_char, int *char_loc) {
	full_string[*char_loc] = new_char;
	++*char_loc;

	return new_char;
}

// Recursively steps through integer to print left to right
void _handle_with_radix(unsigned int n, int radix, bool calcs_size, int *size_of_format, int *char_loc, char* full_string) {
	if(n != 0) {
		_handle_with_radix(n / radix, radix, calcs_size, size_of_format, char_loc, full_string);

		// Translates int values into corresponding char values
		calcs_size ? *size_of_format++ : _add_char(full_string, n % radix < 10 ? n % radix + '0' : n % radix + 'W', char_loc);
	}
}

void _string_handler(char* string, bool calcs_size, int *size_of_format, int *char_loc, char* full_string) {
	do {
		calcs_size ? *size_of_format++ : _add_char(full_string, *string, char_loc);
	} while (*string++ != '\0');
}

void _integer_handler(int n, int radix, char* prefix, bool calcs_size, int *size_of_format, int *char_loc, char* full_string) {

	if(n < 0){
		calcs_size ? *size_of_format++ : _add_char(full_string, '-', char_loc); 
	}

	while (*prefix != '\0') {
		calcs_size ? *size_of_format++ : _add_char(full_string, *prefix, char_loc);
		++prefix;
	}
	
	if(n == 0) {
		calcs_size ? *size_of_format++ : _add_char(full_string, '0', char_loc);
	} else {
		unsigned int abs_num = n < 0 ?-n : n;
		_handle_with_radix(abs_num, radix, calcs_size, size_of_format, char_loc, full_string);
	}
}

void _double_handler(double n, bool calcs_size, int *size_of_format, int *char_loc, char* full_string) {
	_integer_handler((int)n, 10, "$", calcs_size, size_of_format, char_loc, full_string);
	calcs_size ? *size_of_format++ : _add_char(full_string, '.', char_loc);
	_integer_handler((int) ((n - (int) n) * 100), 10, "", calcs_size, size_of_format, char_loc, full_string); 
}

void _format_string_handler(const char *format, int *size_of_format, char* full_string, bool calcs_size, int* char_loc, va_list args_orig) {
	do {
		if (*format != '%') {
			calcs_size ? *size_of_format++ : _add_char(full_string, *format, char_loc);
		} else {
			format++;
			switch (*format) {
				case 'd':  // Decimal integer
					_integer_handler(va_arg(args_orig, int), 10, "", calcs_size, size_of_format, char_loc, full_string);
					break;
				case 'x':  // Hex Integer
					_integer_handler(va_arg(args_orig, int), 16, "0x", calcs_size, size_of_format, char_loc, full_string);
					break;
				case 'b':  // Binary Integer
					_integer_handler(va_arg(args_orig, int), 2, "0b", calcs_size, size_of_format, char_loc, full_string);
					break;		
				case '$':  // Double
					_double_handler(va_arg(args_orig, double), calcs_size, size_of_format, char_loc, full_string);
					break;		
				case 's':  // String
					_string_handler(va_arg(args_orig, char*), calcs_size, size_of_format, char_loc, full_string);
					break;
				case 'c':  // Char
					if (calcs_size) {
						va_arg(args_orig, int);
						++*size_of_format;
					} else {
						_add_char(full_string, va_arg(args_orig, int), char_loc);
					}
					break;		
				case '\0': // Exceptions
					format--;
					calcs_size ? *size_of_format++ : _add_char(full_string, '\0', char_loc);
					break;
				case '%':
					calcs_size ? *size_of_format++ : _add_char(full_string, '%', char_loc);
					break;	
				default:
					calcs_size ? *size_of_format++ : _add_char(full_string, '%', char_loc);
					calcs_size ? *size_of_format++ : _add_char(full_string, *format, char_loc);
			}
			format++;
		}
	} while (*format++ != '\0');
	if(*format == '\0'){
		calcs_size ? *size_of_format++ : _add_char(full_string, '\0', char_loc);
	}
}
	
char* smintf(const char *format, ...) {
	va_list args_orig, args_copy;
	va_start(args_orig, format);
	va_copy(args_copy, args_orig);

	// Finds size of entire string and format string
	int size_of_format = 0;
	int current_char_loc = 0;
	char* malloc_string = NULL;
	_format_string_handler(format, &size_of_format, malloc_string, true, &current_char_loc, args_orig);

	// Puts values into new string
	malloc_string = malloc(sizeof(*format) * size_of_format);
	_format_string_handler(format, &size_of_format, malloc_string, false, &current_char_loc, args_copy);

	va_end(args_orig);
	va_end(args_copy);
	
	return malloc_string;
}

#endif
