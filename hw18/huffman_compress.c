#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "simple_file_utilities.h"
#include "bit_writer.h"
#include "huffman.h"
#include "priority_queue.h"
#include "frequencies.h"
#include "huffman_compress.h"

static void _write_metadata(Metadata data, FILE* out_file) {
	fwrite(&(data.compressed_file_size_bytes), sizeof(data.compressed_file_size_bytes), 1, out_file);
	fwrite(&(data.coding_table_size_bytes), sizeof(data.coding_table_size_bytes), 1, out_file);
	fwrite(&(data.uncompressed_file_size_bytes), sizeof(data.uncompressed_file_size_bytes), 1, out_file);
}

static void _write_table(const char* out_path,TreeNode* root) {
	BitWriter table_writer = open_bit_writer(out_path);
	write_coding_table(root, &table_writer);
	flush_bit_writer(&table_writer);
	close_bit_writer(&table_writer);
}

static void _write_data(const char* in_path, const char* out_path, TreeNode* root) {
	BitWriter compressed_writer = open_bit_writer(out_path);
	write_compressed(root, &compressed_writer, in_path);
	close_bit_writer(&compressed_writer);
}

const char* check_command_line_arguments(int argc, const char* argv[]) {
	if(argc != 3) {
		return ERROR_MSG_USAGE;
	}

	const char* in_path = argv[1];
	const char* out_path = argv[2];

	if(*in_path == '\0') {
		return ERROR_MSG_INPUT_PATH_BLANK;
	}

	if(!does_path_exist(in_path)) {
		return ERROR_MSG_INPUT_PATH_DOES_NOT_EXIST;
	}

	if(!is_path_a_regular_file(in_path)) {
		return ERROR_MSG_INPUT_PATH_NOT_A_FILE;
	}

	FILE* valid_file = fopen(in_path, "r");
	if(valid_file == NULL) {
		return ERROR_MSG_INPUT_PATH_NOT_READABLE;
	} else {
		fclose(valid_file);
	}

	if(*out_path == '\0') {
		return ERROR_MSG_OUTPUT_PATH_BLANK;
	}

	if(does_path_exist(out_path)) {
		return ERROR_MSG_OUTPUT_PATH_EXISTS;
	}

	if(!is_containing_directory_writable(out_path)) {
		return ERROR_MSG_OUTPUT_DIR_NOT_WRITABLE;
	}

	return NULL;
}

Metadata compress_file(const char* in_path, const char* out_path) {
	Metadata header = (Metadata) {.compressed_file_size_bytes = 0, .coding_table_size_bytes = 0, .uncompressed_file_size_bytes = get_file_size_bytes(in_path)};
	FILE* orig_meta_file = fopen(out_path, "w");
	_write_metadata(header, orig_meta_file);
	fclose(orig_meta_file);

	Frequencies freqs = {0};
	const char** a_error = NULL;
	calc_frequencies(freqs, in_path, a_error);
	Node* head = make_huffman_pq(freqs);
	TreeNode* root = make_huffman_tree(head);

	_write_table(out_path, root);
	header.coding_table_size_bytes = get_file_size_bytes(out_path) - 12;
	_write_data(in_path, out_path, root);
	header.compressed_file_size_bytes = get_file_size_bytes(out_path);

	remove_file_if_exists(out_path);

	FILE* final_file = fopen(out_path, "a");
	_write_metadata(header, final_file);
	fclose(final_file);
	_write_table(out_path, root);
	_write_data(in_path, out_path, root);

	return header;
}


/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
