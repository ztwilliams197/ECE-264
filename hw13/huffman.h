#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <stdlib.h>
#include "frequencies.h"
#include "priority_queue.h"

typedef struct Node {
	uchar character;
	size_t frequency;
	struct Node* left;
	struct Node* right;
} TreeNode;

Node* make_huffman_pq(Frequencies freqs);

#endif

#define HUFFMAN_H_V0
