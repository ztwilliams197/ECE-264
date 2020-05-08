#ifndef __SORTS_H__
#define __SORTS_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct _Node{
	int value;
	struct _Node* left;
	struct _Node* right;
} BSTNode;

typedef struct {
	BSTNode* root;
	int size;
} BST;

void tree_sort_array(int* array, size_t size);
void quick_sort_array(int* array, size_t size);
BST create_bst(const int* array, int size);
void empty_bst(BST* bst);

#endif

#define SORTS_H_VERSION_1
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
