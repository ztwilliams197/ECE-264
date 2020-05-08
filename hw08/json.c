#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"

Node* _create_node() {
	Node* temp = malloc(sizeof(*temp));
	temp->next = NULL;
	temp->element = (Element) {.type = ELEMENT_INT, .as_list = NULL};
	return temp;
}

void _destroy_list(Node** a_head) {

	while (*a_head != NULL) { // Iterate in a_head freeing each node until the list is empty
		Node* temp = (*a_head)->next;
		free_element((*a_head)->element);
		free(*a_head);
		*a_head = temp;
	}

	assert(*a_head == NULL);  // List must be empty when destroy_list(…) returns
}

void _eat_spaces(char** a_pos) {

	while(isspace(**a_pos) || **a_pos == '\n' || **a_pos == '\t') { // Gets rid of white space
		++(*a_pos);
	}
}

void _print_list(Node* a_head) {
	Node* curr = a_head;
	while(curr != NULL) {
		print_element(curr->element);
		curr = curr->next;
		if(curr != NULL) {
			printf(", ");
		}
	}
}

bool parse_int(int* a_value, char** a_pos) {
	bool contains_int_literal = true;
	bool is_negative = false;

	// Checks if the value is a valid int literal
	if(isdigit(**a_pos) || (**a_pos == '-' && isdigit(*(*a_pos + 1)))) {

		if( **a_pos == '-') { // Checks if the value is negative
			is_negative = true;
			++(*a_pos);
		}

		*a_value = 0;
		while(**a_pos != '\0' && isdigit(**a_pos)) { // Iterates through *a_pos and setting *a_value
			*a_value *= 10;							 // corresponding to the string at *a_pos
			*a_value += (int)**a_pos - '0';
			++(*a_pos);
		}

		if(is_negative) { // Makes *a_value negative if there was a negative sign in front of it
			*a_value *= -1;
		}
	} else {
		contains_int_literal = false;
	}

	return contains_int_literal;
}

bool parse_string(char** a_string, char** a_pos) {
	bool contains_json_string = true;
	char* temp_pos = *a_pos;

	int num_chars = 1;
	if(**a_pos != '"') { // Tests if there is a '"' at the beginning of the string
		contains_json_string = false;
	} else {
		++(*a_pos);
	}

	if(contains_json_string) {
		while(**a_pos != '"' && (**a_pos != '\n') && **a_pos != '\0') { // Finds length of string
			num_chars++;
			++(*a_pos);
		}
	}
	
	if(**a_pos == '\n' || **a_pos == '\0' || (**a_pos == '"' && *(*a_pos - 1) == '"')) { // Determines
		contains_json_string = false;													 // if string is valid
	}

	if(contains_json_string) { // If string is valid, allocates memory for a_string and copies value of a_pos into a_string
		char** first_char = a_string;
		*a_pos = temp_pos + 1;
		*a_string = malloc(sizeof(char) * (num_chars + 1));
		do {
			**a_string = **a_pos;
			++(*a_pos);
		} while(**a_pos != '"');
		++(*a_pos);
		**a_string = '\0';
		a_string = first_char;
	}

	return contains_json_string;
}

bool parse_element(Element* a_element, char** a_pos) {
	bool valid_json = true;

	_eat_spaces(a_pos);

	if(isdigit(**a_pos) || (**a_pos == '-')) { // Depending on the first char, calls one of the parse functions or returns false
		valid_json = parse_int(&(a_element->as_int), a_pos);
		a_element->type = ELEMENT_INT;
	} else if(**a_pos == '"') {
		valid_json = parse_string(&(a_element->as_string), a_pos);
		a_element->type = ELEMENT_STRING;
	} else if(**a_pos == '[') {
		valid_json = parse_list(&(a_element->as_list), a_pos);
		a_element->type = ELEMENT_LIST;
	} else {
		valid_json = false;
	}

	return valid_json;
}

bool parse_list(Node** a_head, char** a_pos) {
	bool valid_list = true;
	*a_head = NULL;

	if(**a_pos == '[') {
		++(*a_pos);
	} else {
		valid_list = false;
	}

	if(valid_list) {
		Node** curr = a_head;
		if(**a_pos != ']' && **a_pos != ',' && valid_list) {
			*a_head = _create_node();

			while(**a_pos != ']' && valid_list && **a_pos != '\0') {
				valid_list = parse_element(&((*curr)->element), a_pos);
				_eat_spaces(a_pos);

				if(valid_list == false) {
					((*curr)->element).as_list = NULL;
				}
			
				if(**a_pos == ',' && valid_list == true) {
					++(*a_pos);
					Node* temp = _create_node();
					(*curr)->next = temp;
					curr = &temp;
				}
			}
		}

		if(**a_pos == ']') {
			++(*a_pos);
		} else {
			valid_list = false;
		}
	}

	if(!valid_list) {
		_destroy_list(a_head);
		*a_head = NULL;
	}

	return valid_list;
}

void free_element(Element element) {
	if(element.type == ELEMENT_STRING) { // Depending on type, frees variable within element
		free(element.as_string);
	} else if(element.type == ELEMENT_LIST) {
		_destroy_list(&(element.as_list));
	}
}

void print_element(Element element) {

	if(element.type == ELEMENT_INT) { // Depending on type, prints out variable within element
		printf("%d", element.as_int);
	} else if(element.type == ELEMENT_STRING) {
		printf("\"%s\"", element.as_string);
	} else if(element.type == ELEMENT_LIST) {
		printf("[");
		if((element.as_list) != NULL) {
		_print_list(element.as_list);
		}
		printf("]");
	}
}
