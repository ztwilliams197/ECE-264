#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "huffman.h"
#include "miniunit.h"

static int _int_cmp(const void* num1, const void* num2) {
	return *(const int*)num1 - *(const int*)num2;
}

static int _string_cmp(const void* string1, const void* string2) {
	return strcmp((const char*)string1, (const char*)string2);
} 

static void _destroy_value(void* value) {
	free(value);
}

static char* _create_string(const char* orig_string) {
	char* new_string = malloc(sizeof(*new_string) * (strlen(orig_string) + 1));
	return strcpy(new_string, orig_string);
}

static int _test_pq() {
	mu_start();

	Node* head = NULL;
	int* num_1 = malloc(sizeof(int));
	*num_1 = 5;
	pq_enqueue(&head, num_1, _int_cmp);
	mu_check((*(int*)(head->a_value) == 5));
	mu_check((head->next == NULL));

	int* num_2 = malloc(sizeof(int));
	*num_2 = 2;
	pq_enqueue(&head, num_2, _int_cmp);
	mu_check((*(int*)(head->a_value) == 2));
	mu_check((head->next != NULL));
	mu_check((*(int*)(head->next->a_value) == 5));

	int* num_3 = malloc(sizeof(int));
	*num_3 = 7;
	pq_enqueue(&head, num_3, _int_cmp);
	mu_check((*(int*)(head->next->next->a_value) == 7));
	mu_check((head->next->next != NULL));

	Node* temp = pq_dequeue(&head);
	destroy_list(&temp, _destroy_value);
	mu_check((*(int*)(head->a_value) == 5));
	mu_check((head->next->next == NULL));

	destroy_list(&head, _destroy_value);

	char* string_1 = _create_string("Hello");
	pq_enqueue(&head, string_1, _string_cmp);
	mu_check((strcmp(string_1, (char*)head->a_value) == 0));
	mu_check((head->next == NULL));

	char* string_2 = _create_string("A");
	pq_enqueue(&head, string_2, _string_cmp);
	mu_check((strcmp(string_2, (char*)head->a_value) == 0));
	mu_check((head->next != NULL));
	mu_check((strcmp(string_1, (char*)head->next->a_value) == 0));

	destroy_list(&head, _destroy_value);

	mu_end();
}

int _test_stack() {
	mu_start();

	Node* head = NULL;
	int* num_1 = malloc(sizeof(int));
	*num_1 = 5;
	stack_push(&head, num_1);
	mu_check((*(int*)(head->a_value) == 5));
	mu_check((head->next == NULL));

	int* num_2 = malloc(sizeof(int));
	*num_2 = 2;
	stack_push(&head, num_2);
	mu_check((*(int*)(head->a_value) == 2));
	mu_check((head->next != NULL));
	mu_check((*(int*)(head->next->a_value) == 5));

	int* num_3 = malloc(sizeof(int));
	*num_3 = 7;
	stack_push(&head, num_3);
	mu_check((*(int*)(head->a_value) == 7));
	mu_check((head->next->next != NULL));
	
	Node* temp = stack_pop(&head);
	destroy_list(&temp, _destroy_value);
	mu_check((*(int*)(head->a_value) == 2));
	mu_check((head->next->next == NULL));

	destroy_list(&head, _destroy_value);

	char* string_1 = _create_string("Hello");
	stack_push(&head, string_1);
	mu_check((strcmp(string_1, (char*)head->a_value) == 0));
	mu_check((head->next == NULL));

	char* string_2 = _create_string("A");
	stack_push(&head, string_2);
	mu_check((strcmp(string_2, (char*)head->a_value) == 0));
	mu_check((head->next != NULL));
	mu_check((strcmp(string_1, (char*)head->next->a_value) == 0));

	destroy_list(&head, _destroy_value);

	mu_end();
}

int main(int argc, char* argv[]) {

	mu_run(_test_pq);
	mu_run(_test_stack);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
