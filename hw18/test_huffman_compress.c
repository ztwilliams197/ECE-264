#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "miniunit.h"
#include "huffman_compress.h"
#include "simple_file_utilities.h"

const char* _IN_PATH   = "dummy.txt";
const char* _OUT_PATH  = "dummy.txt.hc";
const char* _DUMMY_MSG = "This file is used by " __FILE__ ".";

#define mu_check_strings_equal(s1, s2) mu_check(                    \
	(((s1) == NULL) && ((s2) == NULL)) ||                           \
	(((s1) != NULL) && ((s2) != NULL) && (strcmp((s1), (s2)) == 0)) \
)

static void _write_dummy_file(const char* path, const char contents[]);
static bool _check_file_contents(const char* path, const uint8_t* bytes, size_t num_bytes);


static int _test_input_file_non_existant() {
	mu_start();
	//────────────────────

	// Remove both input and output files, if they exist.
	remove_file_if_exists(_IN_PATH);
	remove_file_if_exists(_OUT_PATH);

	// Set up and check command line arguments
	const char* argv[] = { "./huffman_compress", "MISSING.txt", "MISSING.txt.hc" };
	int argc = sizeof(argv) / sizeof(*argv); // only works for stack array declared with []
	const char* error_msg = check_command_line_arguments(argc, argv);
	mu_check_strings_equal(error_msg, ERROR_MSG_INPUT_PATH_DOES_NOT_EXIST);

	//────────────────────
	mu_end();
}



static int _test_wrong_number_of_arguments() {
	mu_start();
	//────────────────────

	// Set up in_path and out_path
	_write_dummy_file(_IN_PATH, _DUMMY_MSG);
	remove_file_if_exists(_OUT_PATH);

	// Set up command line arguments
	const char* argv[] = { "./huffman_compress", _IN_PATH, _OUT_PATH, "a", "b" };

	// Pretend there are no arguments
	const char* error_msg = check_command_line_arguments(2, argv);
	mu_check_strings_equal(error_msg, ERROR_MSG_USAGE);

	// Pretend there are only 1 argument
	error_msg = check_command_line_arguments(2, argv);
	mu_check_strings_equal(error_msg, ERROR_MSG_USAGE);

	// Pretend there are 2 argument (correct number)
	error_msg = check_command_line_arguments(3, argv);
	if(error_msg) {
		log_yellow("%s\n", error_msg);
	}
	mu_check((error_msg == NULL));

	// Pretend there are 3 arguments (too many)
	error_msg = check_command_line_arguments(4, argv);
	mu_check_strings_equal(error_msg, ERROR_MSG_USAGE);

	// Pretend there are 4 arguments (too many)
	error_msg = check_command_line_arguments(5, argv);
	mu_check_strings_equal(error_msg, ERROR_MSG_USAGE);

	//────────────────────
	mu_end();
}


static int _test_input_file_unreadable() {
	mu_start();
	//────────────────────

	remove_file_if_exists(_OUT_PATH);

	// Set up and check command line arguments
	const char* argv[] = { "./huffman_compress", "/etc/shadow-", _OUT_PATH };
	int argc = sizeof(argv) / sizeof(*argv); // only works for stack array declared with []
	const char* error_msg = check_command_line_arguments(argc, argv);
	mu_check_strings_equal(error_msg, ERROR_MSG_INPUT_PATH_NOT_READABLE);

	//────────────────────
	mu_end();
}


static int _test_input_file_not_file() {
	mu_start();
	//────────────────────

	remove_file_if_exists(_OUT_PATH);

	// Set up and check command line arguments
	const char* argv[] = { "./huffman_compress", "/tmp", _OUT_PATH };
	int argc = sizeof(argv) / sizeof(*argv); // only works for stack array declared with []
	const char* error_msg = check_command_line_arguments(argc, argv);
	mu_check_strings_equal(error_msg, ERROR_MSG_INPUT_PATH_NOT_A_FILE);

	//────────────────────
	mu_end();
}


static int _test_output_dir_not_writable() {
	mu_start();
	//────────────────────

	_write_dummy_file(_IN_PATH, "");

	// Set up and check command line arguments
	const char* argv[] = { "./huffman_compress", _IN_PATH, "/etc/MISSING.txt" };
	int argc = sizeof(argv) / sizeof(*argv); // only works for stack array declared with []
	const char* error_msg = check_command_line_arguments(argc, argv);
	mu_check_strings_equal(error_msg, ERROR_MSG_OUTPUT_DIR_NOT_WRITABLE);

	//────────────────────
	mu_end();
}


static int _test_output_path_blank() {
	mu_start();
	//────────────────────

	_write_dummy_file(_IN_PATH, "");

	// Set up and check command line arguments
	const char* argv[] = { "./huffman_compress", _IN_PATH, "" };
	int argc = sizeof(argv) / sizeof(*argv); // only works for stack array declared with []
	const char* error_msg = check_command_line_arguments(argc, argv);
	mu_check_strings_equal(error_msg, ERROR_MSG_OUTPUT_PATH_BLANK);

	//────────────────────
	mu_end();
}


static int _test_input_path_blank() {
	mu_start();
	//────────────────────

	remove_file_if_exists(_OUT_PATH);

	// Set up and check command line arguments
	const char* argv[] = { "./huffman_compress", "", _OUT_PATH };
	int argc = sizeof(argv) / sizeof(*argv); // only works for stack array declared with []
	const char* error_msg = check_command_line_arguments(argc, argv);
	mu_check_strings_equal(error_msg, ERROR_MSG_INPUT_PATH_BLANK);

	//────────────────────
	mu_end();
}


static int _test_output_path_exists() {
	mu_start();
	//────────────────────

	// Set up in_path and out_path
	_write_dummy_file(_IN_PATH, "");
	_write_dummy_file(_OUT_PATH, "");

	// Set up and check command line arguments
	const char* argv[] = { "./huffman_compress", _IN_PATH, _OUT_PATH };
	int argc = sizeof(argv) / sizeof(*argv); // only works for stack array declared with []
	const char* error_msg = check_command_line_arguments(argc, argv);
	mu_check_strings_equal(error_msg, ERROR_MSG_OUTPUT_PATH_EXISTS);

	//────────────────────
	mu_end();
}


static int _test_empty_input_file() {
	mu_start();
	//────────────────────

	// Set up in_path and out_path
	_write_dummy_file(_IN_PATH, "");
	remove_file_if_exists(_OUT_PATH);

	// Set up and check command line arguments
	const char* argv[] = { "./huffman_compress", _IN_PATH, _OUT_PATH };
	int argc = sizeof(argv) / sizeof(*argv); // only works for stack array declared with []
	const char* error_msg = check_command_line_arguments(argc, argv);
	mu_check((error_msg == NULL));

	// Check contents of file
	uint8_t expected[] = { 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 };
	size_t num_bytes = sizeof(expected) / sizeof(*expected);  // only for array on stack!!!
	_check_file_contents(_IN_PATH, expected, num_bytes);

	//────────────────────
	mu_end();
}


static int _test_huffman_fluffs_many_mums() {
	mu_start();
	//────────────────────

	// Set up in_path and out_path
	const char* message = "huffman fluffs many mums";
	_write_dummy_file(_IN_PATH, message);
	remove_file_if_exists(_OUT_PATH);

	// Set up and check command line arguments
	const char* argv[] = { "./huffman_compress", _IN_PATH, _OUT_PATH };
	int argc = sizeof(argv) / sizeof(*argv); // only works for stack array declared with []
	const char* error_msg = check_command_line_arguments(argc, argv);
	mu_check((error_msg == NULL));

	// Compress the file
	compress_file(_IN_PATH, _OUT_PATH);

	// Check contents of file
	uint8_t expected[] = {
		//______________________________________________
		// OUTPUT DATA for "huffman fluffs many mums"
		//

		//______________________________________________
		// METADATA (12 bytes)
		0x23, 0x00, 0x00, 0x00,   // metadata.compressed_file_size_bytes
		0x0d, 0x00, 0x00, 0x00,   // metadata.coding_table_size_bytes
		0x18, 0x00, 0x00, 0x00,   // metadata.uncompressed_file_size_bytes

		//______________________________________________
		// CODING TABLE plus the tailing 0 bit (13 bytes)
		0xb3, // 10110011 ⇒ 1 ────────── leaf
			  // ⌂└────── │  0110011↵ ── 'f' (01100110₂)
		0x5a, // 01011010 ⇒ 0… ───────── ↑
			  // ┘⌂└───── │  1 ───────── leaf
			  //          │   011010↵ ── 'h' (01101000₂)
		0x2d, // 00101101 ⇒ 00 ───────── ↑
			  // ─┘⌂└──── │   1 ──────── leaf
			  //          │    01101↵ ── 'l' (01101100₂)
		0x89, // 10001001 ⇒ 100 ──────── ↑
			  // ──┘⌂⌂└── │    0 ─────── non─leaf (×2)
			  //          │     1 ────── leaf
			  //          │      001↵ ── ' ' (00100000₂)
		0x01, // 00000001 ⇒ 00000 ────── ↑
			  // ────┘⌂⌂⌂ │      0 ───── non─leaf (×5)
			  //          │       0 ──── non─leaf (×10)
			  //          │        1 ─── leaf
		0x75, // 01110101 ⇒ 01110101 ─── 'u' (01110101₂)
		      // └──────┘ │
		0xbc, // 10111100 ⇒ 1 ────────── leaf
			  // ⌂└────── │  0111100↵ ── 'y' (01111001₂)
		0xd8, // 11011000 ⇒ 1 ────────── ↑
			  // ┘⌂└───── │  1 ───────── leaf
			  //          │   011000↵ ── 'a' (01100001₂)
		0x4b, // 01001011 ⇒ 01 ───────── ↑
			  // ─┘⌂⌂⌂└── │   0 ──────── non─leaf (×3)
			  //          │    0 ─────── non─leaf (×6)
			  //          │     1 ────── leaf
			  //          │      011↵ ── 'm' (01101101₂)
		0x6d, // 01101101 ⇒ 01101 ────── ↑
			  // ────┘⌂└─ │      1 ───── leaf
			  //          │       01↵ ── 'n' (01101110₂)
		0xba, // 10111010 ⇒ 101110 ───── ↑
			  // ─────┘⌂└ │       1 ──── leaf
			  //          │        0↵ ── 's' (01110011₂)
		0xe6, // 11100110 ⇒ 1110011 ──── ↑
			  // ──────┘⌂ │        0 ─── non─leaf (×4)
		0x00, // 0000₀₀₀₀ ⇒ 0 ────────── non─leaf (×8)
			  // ⌂⌂⌂▲⋯⋯⋯⋯    0 ───────── non─leaf (×14)
			  //              0 ──────── non─leaf (×24)
			  //               0 ─────── extra zero to signal end
			  //                ₀ ────── padding
			  //                 ₀ ───── padding
			  //                  ₀ ──── padding
			  //                   ₀ ─── padding

		//______________________________________________
		// Payload (10 bytes)
		0x48, // 01001000   h___u__f
		0x1a, // 00011010   _f_m__a_
		0xf9, // 11111001   __n___ _
		0x8b, // 10001011   _f_l___u
		0x03, // 00000011   __f_f_s_
		0xde, // 11011110   __ __m__
		0xbe, // 10111110   a___n___
		0xa7, // 10100111   y___ __m
		0xa6, // 10100110   __u__m__
		0xf0  // 11110000   s___    
	};

	size_t num_bytes = sizeof(expected) / sizeof(*expected);  // only for array on stack!!!
	mu_check(_check_file_contents(_OUT_PATH, expected, num_bytes));

	//────────────────────
	mu_end();
}


static bool _check_file_contents(const char* path, const uint8_t* bytes, size_t num_bytes) {
	/* Return true iff and only if the file at «path» contains exactly «num_bytes»
	 * bytes, and all bytes match the contents of the array «bytes».
	 */
	bool are_contents_correct = true;

	FILE* fp = fopen(path, "r");
	for(int i = 0; i < num_bytes; i++) {
		uint8_t ch = fgetc(fp);
		if(feof(fp) || ch != bytes[i]) {  // intentionally redundant, for clarity
			are_contents_correct = false;
			break;
		}
	}

	// If size matches
	are_contents_correct = are_contents_correct && ! feof(fp);
	if(are_contents_correct) {
		fgetc(fp);
		are_contents_correct = feof(fp);
	}
	return are_contents_correct;
}


static void _write_dummy_file(const char* path, const char contents[]) {
	/* Write the string «contents» to a file at «path».
	 */
	FILE* fp = fopen(path, "w");
	fprintf(fp, "%s", contents);
	fclose(fp);
}


int main(int argc, char* argv[]) {
	// Make a couple dummy files to test with.
	mu_run(_test_wrong_number_of_arguments);
	mu_run(_test_input_file_non_existant);
	mu_run(_test_input_file_not_file);
	mu_run(_test_input_file_unreadable);
	mu_run(_test_input_path_blank);
	mu_run(_test_output_dir_not_writable);
	mu_run(_test_output_path_blank);
	mu_run(_test_output_path_exists);
	mu_run(_test_empty_input_file);
	mu_run(_test_huffman_fluffs_many_mums);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
