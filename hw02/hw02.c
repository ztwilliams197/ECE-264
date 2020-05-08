#include <stdio.h>
#include "hw02.h"

// Recursively steps through integer to print left to right
void convert_num(unsigned int n, int radix) {
	if(n != 0) {
		convert_num(n / radix, radix);

		// Translates int values into corresponding char values
		fputc(n % radix  < 10 ? n % radix  + '0' : n % radix  + 'W', stdout);
	}
}

void print_integer(int n, int radix, char* prefix) {

	if(n < 0){
		fputc('-',stdout);
	}

	while(*prefix != '\0') {
		fputc(*prefix++,stdout);
	}
	
	if(n == 0) {
		fputc('0', stdout);
	} else {
		unsigned int abs_num = n < 0 ?-n : n;
		convert_num(abs_num, radix);
	}
}
/* vim: set tabstop=2 shiftwidth=2 noexpandtab*/
