#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <stdlib.h>
#include "frequencies.h"
#include "priority_queue.h"
#include "bit_writer.h"

#define FREQ_SIZE 256

typedef struct Node {
	uchar character;
	size_t frequency;
	struct Node* left;
	struct Node* right;
} TreeNode;

Node* make_huffman_pq(Frequencies freqs);
TreeNode* make_huffman_tree(Node* head);
void destroy_huffman_tree(TreeNode** a_root);
void write_coding_table(TreeNode* root, BitWriter* a_writer);
void write_compressed(TreeNode* root, BitWriter* a_writer, const char* in_path);

#endif

#define HUFFMAN_H_V0
