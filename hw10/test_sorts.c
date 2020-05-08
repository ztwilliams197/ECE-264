#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "miniunit.h"
#include "sorts.h"

void _print_array(int* array, size_t size) {
	printf("[");
	for(int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("]\n");
}

int _test_empty_list() {
	mu_start();

	BST bst = create_bst(NULL, 0);
	mu_check((bst.size == 0));
	mu_check((bst.root == NULL));
	empty_bst(&bst);

	int* array = NULL;
	_print_array(array, 0);
	tree_sort_array(array, 0);
	quick_sort_array(array,0);
	mu_check((array == NULL));

	mu_end();
}

int _test_nonempty_bst() {
	mu_start();

	int array[6] = {3,6,1,7,2,0};
	BST bst = create_bst(array, 6);
	mu_check((bst.root->value == 3));
	mu_check((bst.root->left->value == 1));
	mu_check((bst.root->right->value == 6));
	empty_bst(&bst);

	_print_array(array, 6);
	tree_sort_array(array, 6);
	_print_array(array, 6);

	mu_end();	
}

int _test_nonempty_quick_sort() {
	mu_start();

	int array[10] = {2,3,5,1,6,4,7,9,8,10};
	_print_array(array, 10);
	quick_sort_array(array, 10);
	_print_array(array, 10);

	mu_end();
}

int main(int argc, char* argv[]) {

	mu_run(_test_empty_list);
	mu_run(_test_nonempty_bst);
	mu_run(_test_nonempty_quick_sort);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
