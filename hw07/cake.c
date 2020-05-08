#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "clog.h"  // optional
#include "cake.h"

struct Node* _create_node(const char* name) {
	struct Node* temp = malloc(sizeof(*temp));
	*temp = (struct Node) { .name = name, .next = NULL };
	return temp;
}


struct Node* create_list(const char* first_name, ...) {
	struct Node* head = NULL;
	struct Node* tail = NULL;

	if(first_name != NULL) { 
		va_list args;
		va_start(args, first_name);
		head = _create_node(first_name);
		tail = head;

		// Takes each name other than first_name and creates node for each one
		// Connect previous node to new node
		char* next_name = va_arg(args, char*);
		while(next_name != NULL) {
			tail->next = _create_node(next_name);
			tail = tail->next;
			next_name = va_arg(args, char*);
		}
		tail->next = head; // Link last node to head
	}

	assert((first_name == NULL && head == NULL) ||
		   (first_name != NULL && head -> name == first_name));

	return head;
}


void print_list(const struct Node* start_node) {

	// If the list is not empty, create a temporary node to hold the value of *start_node
	// Iterate through linked list printing names and keeping track of string length
	// Otherwise, print "EMPTY" if the list has no nodes
	if(start_node != NULL) {
		int string_length = 0;

		struct Node curr = *start_node;
		printf(CORNER_NW);
		while(curr.next != start_node) { //Iterate through all but last node and print
			printf("[\"%s\"]", curr.name);
			string_length += 4 + strlen(curr.name);
			curr = *(curr.next);
			if (curr.next != start_node) {
				printf(BOX_HORIZONTAL_LINE);
				string_length++;
			}
		}

		if(start_node->next != start_node) { // Print last node
			printf(BOX_HORIZONTAL_LINE);
			string_length++;
		}
		printf("[\"%s\"]", curr.name);
		string_length += 4 + strlen(curr.name);

		printf(CORNER_NE);
		printf("\n");

		printf(CORNER_SW);
		for(int i = 0; i < string_length; i++) { // Print line underneath names
			printf(BOX_HORIZONTAL_LINE);
		}
		printf(CORNER_SE);
		printf("\n");
	
	} else {
		printf("EMPTY\n");
	}

}


void destroy_list(struct Node** a_head) {

	while (*a_head != NULL) { // Iterate in a_head freeing each node until the list is empty
		free(detach_next_node(a_head));
	}

	assert(*a_head == NULL);  // List must be empty when destroy_list(…) returns
}


struct Node* get_nth_node(struct Node* start_node, int n) {
	struct Node* node = NULL;

	// Iterate through list n times
	if(start_node != NULL) {
		node = start_node;
		for (int num_skips = 0; num_skips < n; num_skips++) {
			node = node->next;
		}
	}

	assert((node == NULL) == (start_node == NULL));
	return node;
}

void choose_winner(struct Node** a_node, int n) {

	if(*a_node != NULL) { // Eliminates every nth node until only one remains
		while((*a_node)->next != *a_node) {
			*a_node = get_nth_node(*a_node, n-2);
			free(detach_next_node(a_node));
			*a_node = (*a_node)->next;
		}
	}

}

// Pops off and returns the node after *a_node
struct Node* detach_next_node(struct Node** a_node) {
	struct Node* loner = NULL;

	loner = (*a_node)->next;
	if (loner == *a_node) {
		*a_node = NULL;
	} else {
		(*a_node)->next = loner->next;
	}
	loner->next = loner;

	assert((loner != NULL && loner -> next == loner) || *a_node == NULL);

	return loner;

}


size_t count_nodes(const struct Node* node) {
	size_t num_nodes = 0;

	if(node != NULL) {
		struct Node curr = *node;
		do {
			num_nodes++;
			curr = *(curr.next);
		} while(curr.next != node->next);
	}

	return num_nodes;
}

// Tests if the linked list contains a node with a name value "name"
bool has_name(const struct Node* node, const char* name) {
	bool contains_name = false;

	if(node != NULL) {
		struct Node curr = *node;
		do {
			if(strcmp(name,curr.name) == 0) {
				contains_name = true;
			}
			curr = *(curr.next);
		} while(curr.next != node->next && contains_name == false);
	}

	return contains_name;
}

// Tests if the linked list contains the same names in the same order as *names
bool is_names(const struct Node* start_node, size_t num_names, const char** names) {
	bool contains_names = true;

	if(start_node != NULL) {
		struct Node curr = *start_node;
		for(int name = 0; name < num_names; name++) {
			if(strcmp(names[name],curr.name) != 0) {
				contains_names = false;
			}
			curr = *(curr.next);
		}
	} else if (num_names != count_nodes(start_node)) {
		contains_names = false;
	} else {
		contains_names = false;
	}

	return contains_names;
}


#define CAKE_C_VERSION 5
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
