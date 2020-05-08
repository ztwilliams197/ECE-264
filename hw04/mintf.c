#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include "mintf.h"

// Recursively steps through integer to print left to right
void print_with_radix(unsigned int n, int radix) {
	if(n != 0) {
		print_with_radix(n / radix, radix);

		// Translates int values into corresponding char values
		fputc(n % radix  < 10 ? n % radix  + '0' : n % radix  + 'W', stdout);
	}
}

// Determines if percent is valid asking for args
bool valid_percent(char next_char) {
	bool valid = true;
	switch (next_char) { 
		case 'd':
		case 'x':
		case 'b':
		case '$':
		case 's':
		case 'c':
			valid = false;
	}

	return valid;
}

void print_string(char* string) {
	while(*string != '\0') {
		fputc(*string++, stdout);
	}
}

void print_integer(int n, int radix, char* prefix) {

	if(n < 0){
		fputc('-',stdout);
	}

	print_string(prefix);
	
	if(n == 0) {
		fputc('0', stdout);
	} else {
		unsigned int abs_num = n < 0 ?-n : n;
		print_with_radix(abs_num, radix);
	}
}

void print_double(double n) {

	int temp_concat = (int)n;
	print_integer(temp_concat, 10, "$");

	int temp_deci = (n - (int)n) * 100;
	print_integer(temp_deci, 10, ".");
}

void mintf(const char *format, ...) {

	// Determines number of format codes
	int percent_count = 0;
	const char *temp_format = format;
	while(*temp_format != '\0') {
		if(*temp_format++ == '%' && valid_percent(*temp_format + 1)) {
			percent_count++;
		}
	}

	// Add arg functionality
	va_list more_args;
	va_start(more_args, format);

	// Prints format filling in format codes
	while(*format != '\0') {
		if(*format != '%') { 
			fputc(*format++, stdout);
		} else {
			format++;
			switch (*format) {
				case 'd':  // Decimal integer
					print_integer(va_arg(more_args, int), 10, "");
					break;
				case 'x':  // Hex Integer
					print_integer(va_arg(more_args, int), 16, "0x");
					break;
				case 'b':  // Binary Integer
					print_integer(va_arg(more_args, int), 2, "0b");
					break;		
				case '$':  // Double
					print_double(va_arg(more_args, double));
					break;		
				case 's':  // String
					print_string(va_arg(more_args, char*));
					break;
				case 'c':  // Char
					fputc(va_arg(more_args, int), stdout);
					break;		
				case '\0': // Exceptions
					format--;
				case '%':
					fputc('%', stdout);
					break;	
				default:
					fputc('%', stdout);
					fputc(*format, stdout);
			}
			format++;
		}
	}	
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
