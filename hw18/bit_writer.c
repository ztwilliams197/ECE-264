#include <assert.h>
#include "bit_writer.h"

BitWriter open_bit_writer(const char* path) {
	return (BitWriter) {.file = fopen(path, "a"), .current_byte = 0, .num_bits_left = 8};
}

void write_bits(BitWriter* a_writer, uint8_t bits, uint8_t num_bits_to_write) {
	assert(num_bits_to_write >= 0 && num_bits_to_write <= 8);
	assert(a_writer->num_bits_left >= 1 && a_writer->num_bits_left <= 8);

	uint8_t bit_set1 = (0xff >> (8 - num_bits_to_write)) & bits;

	if(num_bits_to_write > a_writer->num_bits_left) {
		int len_second_bit = num_bits_to_write - a_writer->num_bits_left;
		uint8_t bit_set2 = bit_set1 << (8 - len_second_bit);
		bit_set1 = bit_set1 >> (len_second_bit);
		
		a_writer->current_byte += bit_set1;
		flush_bit_writer(a_writer);
		a_writer->current_byte += bit_set2;
		a_writer->num_bits_left -= len_second_bit;
	} else {
		bit_set1 = bit_set1 << (a_writer->num_bits_left - num_bits_to_write);
		a_writer->current_byte += bit_set1;
		a_writer->num_bits_left -= num_bits_to_write;

		if(a_writer->num_bits_left == 0) {
			flush_bit_writer(a_writer);
		}
	}

	assert(a_writer->num_bits_left >= 1 && a_writer->num_bits_left <= 8);
}

void flush_bit_writer(BitWriter* a_writer) {
	fputc(a_writer->current_byte, a_writer->file);
	a_writer->current_byte = 0;
	a_writer->num_bits_left = 8;
	fflush(a_writer->file);
}

void close_bit_writer(BitWriter* a_writer) {
	if(a_writer->current_byte != 0) {
		flush_bit_writer(a_writer);
	}
	fclose(a_writer->file);
}

#define __BIT_WRITER_C_V1__
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab colorcolumn=96: */
