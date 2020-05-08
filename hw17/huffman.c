#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "priority_queue.h"
#include "frequencies.h"
#include "bit_writer.h"
#include "huffman.h"

// Holds bits and num_bits values
typedef struct { uint8_t bits; int num_bits; } _BitCode;

// Helper function to create array of bit codes
static void _create_code_table(_BitCode char_codes[], TreeNode* root, uint8_t bits, int bit_length) {

	// Traverses Left Branch
	if(root->left != NULL) {
		_create_code_table(char_codes, root->left, bits << 1, bit_length + 1);
	}

	// Traverses Right Branch
	if(root->right != NULL) {
		_create_code_table(char_codes, root->right, (bits << 1) + 1, bit_length + 1);
	}

	// Writes char code info if leaf node
	if(root->character != '\0') {
		char_codes[root->character] = (_BitCode) {.bits = bits, .num_bits = bit_length};
	}

}

// Helper function for destroy_huffman_tree()
static void _empty_tree(TreeNode* root) {
	if(root->left != NULL) { // Frees left branch of BST
		_empty_tree(root->left);
	}

	if(root->right != NULL) { // Frees right branch of BST
		_empty_tree(root->right);
	}

	free(root);
}

// Compare function for creating huffman priority queue
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

// Makes huffman priority queue from freqs
Node* make_huffman_pq(Frequencies freqs) {
	Node* head = NULL;

	// Enqueue a Tree with each character without freq 0
	for(int character = 0; character < FREQ_SIZE; character++) {
		if(freqs[character] != 0) {
			TreeNode* new_tree = malloc(sizeof(*new_tree));
			*new_tree = (TreeNode) {.character = character, .frequency = freqs[character], .left = NULL, .right = NULL};
			pq_enqueue(&head, (void*) new_tree, _cmp_trees);
		}
	}

	return head;
}

// Makes huffman tree from priority queue
TreeNode* make_huffman_tree(Node* head) {
	TreeNode* root = NULL;

	if(head != NULL) {
		while(head->next != NULL) {
			// Add first value to left branch in tree
			Node* left_node = pq_dequeue(&head);
			TreeNode* left = (TreeNode*) left_node->a_value;
			free(left_node);

			// Add second value to right branch in tree
			Node* right_node = pq_dequeue(&head);
			TreeNode* right = (TreeNode*) right_node->a_value;
			free(right_node);

			// Create root of tree and connect left and right branches
			TreeNode* new_tree = malloc(sizeof(*new_tree));
			*new_tree = (TreeNode) {.character = '\0', .frequency = left->frequency + right->frequency, .left = left, .right = right};
			pq_enqueue(&head, (void*)new_tree, _cmp_trees);
		}

		// Removes final Node from priority queue
		Node* final_node = pq_dequeue(&head);
		root = (TreeNode*) final_node->a_value;
		free(final_node);
	}

	return root;
}

// Writes coding table in header file from huffman tree
void write_coding_table(TreeNode* root, BitWriter* a_writer) {
	bool complete_tree = false;

	if(root->left != NULL) {
		// Traverses Left Branch
		if(root->left->character == '\0') {
			write_coding_table(root->left, a_writer);
		} else { // Writes 1 and character to file if leaf node is found
			write_bits(a_writer, 1, 1);
			write_bits(a_writer, (uint8_t)root->left->character, 8);
			complete_tree = true;
		}
	}

	if(root->right != NULL) {
		// Traverses Right Branch
		if(root->right->character == '\0') {
			write_coding_table(root->right, a_writer);
		} else { // Writes 1 and character to file if leaf nod is found
			write_bits(a_writer, 1, 1);
			write_bits(a_writer, (uint8_t)root->right->character, 8);
			complete_tree = true;
		}
	} 

	if(root->left == NULL && root->right == NULL) {
		write_bits(a_writer, 1, 1);
		write_bits(a_writer, (uint8_t)root->character, 8);
		complete_tree = true;
	}

	// Writes 0 if branch ended
	if(complete_tree) {
		write_bits(a_writer, 0, 1);
	}
}

// Free all nodes within huffman tree
void destroy_huffman_tree(TreeNode** a_root) {
	_empty_tree(*a_root);
	*a_root = NULL;
}

// Write uncompressed_bytes using compressed bit values to text file
void write_compressed(TreeNode* root, BitWriter* a_writer, uint8_t* uncompressed_bytes) {
	_BitCode char_to_code[256] = {(_BitCode) {.bits = 0, .num_bits = 0}};
	_create_code_table(char_to_code, root, 0, 0);

	while(*uncompressed_bytes != '\0') {
		write_bits(a_writer, char_to_code[*uncompressed_bytes].bits, char_to_code[*uncompressed_bytes].num_bits);
		++(uncompressed_bytes);
	}
	flush_bit_writer(a_writer);
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
