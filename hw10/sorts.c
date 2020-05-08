#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "sorts.h"

// Creates node in the BST with .value = value
BSTNode* _create_node(int value) {
	BSTNode* temp = malloc(sizeof(*temp));
	*temp = (BSTNode) {.value = value, .left = NULL, .right = NULL};
	return temp;
}

void _insert_node(int value, BSTNode** root) {

	if(*root == NULL) { // Inserts node at root
		*root = _create_node(value);	
	} else if((*root)->value > value) { // If value is less than the root value moves to (*root)->left
		_insert_node(value, &((*root)->left));
	} else { // If value is greater than or equal to root value moves to (*root)->right
		_insert_node(value, &((*root)->right));
	}

}

void _traverse_sort(int** array, BSTNode* root) {
	if(root != NULL) { // Does not attempt to sort empty array

		if(root->left != NULL) { // Moves all the way to the left first
			_traverse_sort(array, root->left);
		}

		// Places root value into array
		**array = root->value;
		++(*array);

		// Moves to right after left side and root
		if(root->right != NULL) {
			_traverse_sort(array, root->right);
		}
	}
}

void _traverse_empty(BSTNode* root) {
	if(root->left != NULL) { // Frees left branch of BST
		_traverse_empty(root->left);
	}

	if(root->right != NULL) { // Frees right branch of BST
		_traverse_empty(root->right);
	}

	free(root);
}

BST create_bst(const int* array, int size) {
	// Initializes BST on stack with .size = size
	BST bst = (BST) {.size = size, .root = NULL};

	// Iterates through array, inserting values into BST
	if(size != 0) {
		for(int element = 0; element < size; element++) {
			_insert_node(array[element], &(bst.root));
		}
	}
	
	return bst;
}

void tree_sort_array(int* array, size_t size) {
	BST bst = create_bst(array, size); // Create BST
	_traverse_sort(&array, bst.root); // Sort Array
	empty_bst(&bst); // Free nodes in BST
}

void empty_bst(BST* bst) {
	// Free all nodes in BST and set BST to size 0 and NULL root
	if(bst->size != 0 && bst->root != NULL) {
		_traverse_empty(bst->root);
		*bst = (BST) {.size = 0, .root = NULL};
	}
}

int _cmp_int(const void* num1, const void* num2) {
	return (*(int*)num1 - *(int*)num2); // Compar function for integers
}

void quick_sort_array(int* array, size_t size) {
	qsort(array, size, sizeof(int), _cmp_int); // Uses quick sort to sort array
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
