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

int _test_huffman_pq() {
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

	Node* head = make_huffman_pq(freqs);
	mu_check((head != NULL));
	mu_check((((TreeNode*)head->a_value)->frequency == 1));
	mu_check((((TreeNode*)head->a_value)->character == '\n'));
	mu_check((((TreeNode*)head->next->a_value)->frequency == 1));
	mu_check((((TreeNode*)head->next->a_value)->character == 'e'));

	destroy_list(&head, _destroy_single_node_tree);

	mu_end();
}

int main(int argc, char* argv[]) {

	mu_run(_test_huffman_pq);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
