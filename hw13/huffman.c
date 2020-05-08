#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "priority_queue.h"
#include "frequencies.h"
#include "huffman.h"

#define FREQ_SIZE 256

/*
static void _print_queue(Node* head) {
	Node* temp = head;
	TreeNode* curr = NULL;

	while(temp != NULL) {
		curr = (TreeNode*) temp->a_value;
		printf("Freq: %ld Char: %d -> ", curr->frequency, (curr->character));
		temp = temp->next;
	}
	printf("\n");
}
*/

static int _cmp_trees(const void* tree1, const void* tree2) {
	if((((TreeNode*)tree1)->frequency) != (((TreeNode*)tree2)->frequency)) {
		return (long int)(((TreeNode*)tree1)->frequency) - (long int)(((TreeNode*)tree2)->frequency);
	}

	return (int)(((TreeNode*)tree1)->character) - (int)(((TreeNode*)tree2)->character);
}

Node* make_huffman_pq(Frequencies freqs) {
	Node* head = NULL;

	for(int character = 0; character < FREQ_SIZE; character++) {
		if(freqs[character] != 0) {
			TreeNode* new_tree = malloc(sizeof(*new_tree));
			*new_tree = (TreeNode) {.character = character, .frequency = freqs[character], .left = NULL, .right = NULL};
			pq_enqueue(&head, (void*) new_tree, _cmp_trees);
		}
	}

	return head;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
