#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"


static void _insert_node(Node** prev_node, Node** new_node) {
	(*new_node)->next = (*prev_node)->next;
	(*prev_node)->next = *new_node;
}

// Adds new value to priority queue
Node* pq_enqueue(Node** a_head, void* a_value, int (*cmp_fn)(const void*, const void*)) {
	Node* new_node = malloc(sizeof(*new_node));
	*new_node = (Node) {.a_value = a_value, .next = NULL};

	if(*a_head == NULL || cmp_fn(a_value, (*a_head)->a_value) < 0) {
		new_node->next = *a_head;
		*a_head = new_node;
	} else {
		Node* prev_node = *a_head;
		Node* curr_node = prev_node->next;

		while(curr_node != NULL && cmp_fn(a_value, curr_node->a_value) > 0) {
			prev_node = curr_node;
			curr_node = curr_node->next;
		}

		_insert_node(&prev_node, &new_node);
	}

	return new_node;
}

// Detaches first node from queue
Node* pq_dequeue(Node** a_head) {
	Node* detached_node = NULL;

	if(*a_head != NULL) {
		detached_node = *a_head;
		*a_head = detached_node->next;
		detached_node->next = NULL;
	}

	return detached_node;
}


Node* stack_push(Node** a_top, void* a_value) {
	Node* new_node = malloc(sizeof(*new_node));
	*new_node = (Node) {.a_value = a_value, .next = *a_top};
	*a_top = new_node;
	return *a_top;
}


Node* stack_pop(Node** a_top) {
	Node* detached_node = NULL;

	if(*a_top != NULL) {
		detached_node = *a_top;
		*a_top = detached_node->next;
		detached_node->next = NULL;
	}

	return detached_node;
}


void destroy_list(Node** a_head, void (*destroy_value_fn)(void*)) {
	while(*a_head != NULL) {
		Node* temp = *a_head;
		destroy_value_fn((*a_head)->a_value);
		*a_head = (*a_head)->next;
		free(temp);
	}
}


#define HUFFMAN_C_V0
