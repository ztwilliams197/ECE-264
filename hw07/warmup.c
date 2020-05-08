#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "clog.h"     // optional

// TODO:  Create definition of «struct Rectangle»
struct Rectangle {
	int width;
	int height;
};

struct Rectangle create_rectangle_stack(int height, int width) {
	return (struct Rectangle) { .width = width, .height = height };
}

struct Rectangle* create_rectangle_heap(int height, int width) {
	struct Rectangle* new_rect = malloc(sizeof(*new_rect));
	*new_rect = (struct Rectangle) { .width = width, .height = height};
	return new_rect;
}

void print_rectangle(struct Rectangle rect) {
	for (int height = 0; height < rect.height; height++) {
		for (int width = 0; width < rect.width; width++) {
			printf("*");	
		}
		printf("\n");
	}
}

void destroy_rectangle(struct Rectangle* a_rect) {
	free(a_rect);
}

// TODO:  Create definition of «struct LimerickNode»
struct LimerickNode {
	const char* line;
	struct LimerickNode *next_node;
};

struct LimerickNode* create_limerick(const char* lines[5]) {
	struct LimerickNode *head = malloc(sizeof(*head));
	struct LimerickNode *curr = NULL;

	curr = head;
	for(int line = 0; line < 4; line++) {
		*curr = (struct LimerickNode) { .line = lines[line], .next_node = malloc(sizeof(*curr)) };
		curr = curr->next_node;
	}
	*curr = (struct LimerickNode) { .line = lines[4], .next_node = NULL };

	return head;
}

void destroy_limerick(struct LimerickNode* head) {
	struct LimerickNode* curr_head = head;

	while (curr_head != NULL) {
		struct LimerickNode* next_node = curr_head->next_node;
		free(curr_head);
		curr_head = next_node;
	}
}

void print_limerick(struct LimerickNode* head) {

	for (struct LimerickNode *curr = head; curr != NULL; curr = curr->next_node) {
		printf("%s\n", curr->line);
	}
}

int main(int argc, char* argv[]) {
	struct Rectangle   rect_1 = create_rectangle_stack(3, 5);
	print_rectangle(rect_1);
	printf("\n");

	struct Rectangle* a_rect_2 = create_rectangle_heap(5, 7);
	print_rectangle(*a_rect_2);
	destroy_rectangle(a_rect_2);
	printf("\n");

	const char* lines[5] = {"Hello","You suck","I hope","This Works","Please"};
	struct LimerickNode* limerick = create_limerick(lines);
	print_limerick(limerick);
	destroy_limerick(limerick);
	printf("\n");
}
