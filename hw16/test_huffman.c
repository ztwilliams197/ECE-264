#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include "frequencies.h"
#include "priority_queue.h"
#include "huffman.h"
#include "miniunit.h"

void _destroy_single_node_tree(void* node) {
	free(node);
}

int _test_huffman_tree() {
	mu_start();

	Frequencies freqs = {0};
	const char** a_error = malloc(sizeof(char**));
	*a_error = NULL;
	bool is_valid = calc_frequencies(freqs, "gophers", a_error);
	mu_check(is_valid);
	mu_check((*a_error == NULL));
	mu_check((freqs['g'] == 3));
	mu_check((freqs['o'] == 3));
	mu_check((freqs[' '] == 2));
	free(a_error);

	Node* head = make_huffman_pq(freqs);
	mu_check((head != NULL));
	mu_check((((TreeNode*)head->a_value)->frequency == 1));
	mu_check((((TreeNode*)head->a_value)->character == '\n'));
	mu_check((((TreeNode*)head->next->a_value)->frequency == 1));
	mu_check((((TreeNode*)head->next->a_value)->character == 'e'));

	TreeNode* root = make_huffman_tree(head);
	TreeNode* left = root->left;
	TreeNode* right = root->right;
	mu_check((root != NULL));
	mu_check((root->frequency == 14));
	mu_check((left->frequency == 6));
	mu_check((left->left->character == 'g'));
	mu_check((left->right->character == 'o'));
	mu_check((right->frequency == 8));

	destroy_huffman_tree(&root);
	mu_check((root == NULL));

	mu_end();
}

int _test_huffman_header() {
	mu_start();

	Frequencies gophers_freqs = { ['g'] = 3, ['o'] = 3, [' '] = 2, ['s'] = 1, ['e'] = 1, ['h'] = 1, ['p'] = 1, ['r'] = 1};
	Node* head = make_huffman_pq(gophers_freqs);
	TreeNode* root = make_huffman_tree(head);
	BitWriter a_writer = open_bit_writer("gopher_header.txt");
	write_coding_table(root, &a_writer);
	close_bit_writer(&a_writer);
	destroy_huffman_tree(&root);

	Frequencies one_char = { ['a']= 3 };
	head = make_huffman_pq(one_char);
	root = make_huffman_tree(head);
	a_writer = open_bit_writer("one_char_header.txt");
	write_coding_table(root, &a_writer);
	close_bit_writer(&a_writer);
	destroy_huffman_tree(&root);

	mu_end();
}

int main(int argc, char* argv[]) {

	mu_run(_test_huffman_tree);
	mu_run(_test_huffman_header);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
