#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "priority_queue.h"
#include "frequencies.h"
#include "huffman.h"

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

static void _empty_tree(TreeNode* root) {
	if(root->left != NULL) { // Frees left branch of BST
		_empty_tree(root->left);
	}

	if(root->right != NULL) { // Frees right branch of BST
		_empty_tree(root->right);
	}

	free(root);
}

static int _cmp_trees(const void* tree1, const void* tree2) {
	if((((TreeNode*)tree1)->frequency) != (((TreeNode*)tree2)->frequency)) {
		long int comp_long = (long int)(((TreeNode*)tree1)->frequency) - (long int)(((TreeNode*)tree2)->frequency);
		if(comp_long > 0) {
			return 1;
		} else {
			return -1;
		}
	}

	if( ((TreeNode*)tree1)->character == '\0') {
		return 1;
	} else {
		return (int)(((TreeNode*)tree1)->character) - (int)(((TreeNode*)tree2)->character);
	}
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

TreeNode* make_huffman_tree(Node* head) {
	TreeNode* root = NULL;

	if(head != NULL) {
	// Create huffman tree
		while(head->next != NULL) {
			Node* left_node = pq_dequeue(&head);
			TreeNode* left = (TreeNode*) left_node->a_value;
			free(left_node);

			Node* right_node = pq_dequeue(&head);
			TreeNode* right = (TreeNode*) right_node->a_value;
			free(right_node);

			TreeNode* new_tree = malloc(sizeof(*new_tree));
			*new_tree = (TreeNode) {.character = '\0', .frequency = left->frequency + right->frequency, .left = left, .right = right};
			pq_enqueue(&head, (void*)new_tree, _cmp_trees);
		}

		Node* final_node = pq_dequeue(&head);
		root = (TreeNode*) final_node->a_value;
		free(final_node);
	}

	return root;
}

void destroy_huffman_tree(TreeNode** a_root) {

	_empty_tree(*a_root);
	*a_root = NULL;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
