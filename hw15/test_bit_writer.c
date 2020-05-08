#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "miniunit.h"
#include "clog.h"
#include "bit_writer.h"

int _test_bit_writer(){
	mu_start();

	BitWriter bw = open_bit_writer("test_file.txt");
	write_bits(&bw, 0x05, 3);
	mu_check((bw.current_byte == 160));
	mu_check((bw.num_bits_left == 5));

	write_bits(&bw, 0x07, 4);
	mu_check((bw.current_byte == 174));
	mu_check((bw.num_bits_left == 1));

	write_bits(&bw, 0x0f, 4);
	mu_check((bw.current_byte == 224));
	mu_check((bw.num_bits_left == 5));

	write_bits(&bw, 0x0f, 5);
	mu_check((bw.current_byte == 0));
	mu_check((bw.num_bits_left == 8));
	
	close_bit_writer(&bw);
	
	bw = open_bit_writer("test_file_empty.txt");
	write_bits(&bw, 0x05, 7);
	close_bit_writer(&bw);

	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test_bit_writer);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
