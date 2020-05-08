#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "miniunit.h"
#include "cake.h"

int _test_create_and_destroy_lists() {
	mu_start();

	struct Node* empty = create_list(NULL);
	struct Node* one_name = create_list("Zach", NULL);
	struct Node* mult_names = create_list("Zach", "Jeff", "Eliot", NULL);

	struct Node* sample_one_name = malloc(sizeof(*sample_one_name));
	*sample_one_name = (struct Node) { .name = "Zach", .next = NULL};

	mu_check_lists_eq(NULL, empty);
	mu_check_lists_eq(sample_one_name, one_name);

	destroy_list(&empty);
	destroy_list(&one_name);
	destroy_list(&mult_names);

	mu_end();
}

int main(int argc, char* argv[]) {
	
//	mu_run(_test_create_and_destroy_lists);
	
	struct Node* empty = create_list(NULL);
	struct Node* one_name = create_list("Zach", NULL);
	struct Node* mult_names = create_list("Zach", "Jeff", "Eliot", NULL);
	struct Node* win_test = create_list("Zach", "Jeff", "Henry", "Eliot", NULL);
	struct Node* win_test_more = create_list("Zach", "Jeff", "Eliot", "Vivek", "Kevin", "Sami", NULL);

	print_list(empty);

	print_list(one_name);

	print_list(mult_names);
	mult_names = get_nth_node(mult_names, 2);
	printf("%ld\n", count_nodes(mult_names));
	print_list(mult_names);

	print_list(win_test);
	choose_winner(&win_test, 2);
	print_list(win_test);

	print_list(win_test_more);
	choose_winner(&win_test_more, 3);
	print_list(win_test_more);

	destroy_list(&empty);
	destroy_list(&one_name);
	destroy_list(&mult_names);
	destroy_list(&win_test);
	destroy_list(&win_test_more);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
