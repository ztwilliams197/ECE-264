#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "miniunit.h"
#include "json.h"

int _test_parse_int_valid() { // Tests valid parse_int calls
	mu_start();
	
	int result;
	char* input = "0";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check((pos == input + 1));
	mu_check((result == 0));
	
	input = "15";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check((pos == input + 2));
	mu_check((result == 15));

	input = "-15";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check((pos == input + 3));
	mu_check((result == -15));

	input = "1234AA";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check((pos == input + 4));
	mu_check((result == 1234));

	mu_end();
}

int _test_parse_int_invalid() { // Tests invalid parse_int calls
	mu_start();

	int result;
	char* input = "A";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check((pos == input));

	input = "-A";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check((pos == input));

	input = "-";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check((pos == input));

	mu_end();
}

int _test_parse_string_valid() { // Tests valid parse_string calls
	mu_start();

	Element* result = malloc(sizeof(*result));
	char* input = "\"ABCD\"";
	char* pos = input;
	bool is_success = parse_element(result, &pos);
	mu_check(is_success);
	mu_check((pos == input + 6));
	mu_check(strcmp(result->as_string, "ABCD"));
	free_element(*result);

	input = "\"abc\\\"";
	pos = input;
	is_success = parse_element(result, &pos);
	mu_check(is_success);
	mu_check((pos == input + 6));
	mu_check(strcmp(result->as_string, "abc\\"));
	free_element(*result);

	input = "\"abc\\z\"";
	pos = input;
	is_success = parse_element(result, &pos);
	mu_check(is_success);
	mu_check((pos == input + 7));
	mu_check(strcmp(result->as_string, "abc\\z"));

	free_element(*result);
	free(result);

	mu_end();
}

int _test_parse_string_invalid() { // Tests invalid parse_string calls
	mu_start();

	char* result;
	char* input = "\"ABCD";
	char* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check((pos == input + 5));

	input = "abc\\";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check((pos == input));

	input = "abc\\z";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check((pos == input));

	input = "";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check((pos == input));

	mu_end();
}

int _test_parse_element_valid() { // Tests valid parse_element calls
	mu_start();

	Element result;
	char* input = "12345";
	char* pos = input;
	bool is_success = parse_element(&result, &pos);
	mu_check(is_success);
	mu_check((result.type == ELEMENT_INT));
	mu_check((pos == input + 5));
	mu_check((result.as_int == 12345));
	mu_check((*pos == '\0'));

	input = "-12345";
	pos = input;
	is_success = parse_element(&result, &pos);
	mu_check(is_success);
	mu_check((result.type == ELEMENT_INT));
	mu_check((pos == input + 6));
	mu_check((result.as_int == -12345));
	mu_check((*pos == '\0'));

	input = "   12345";
	pos = input;
	is_success = parse_element(&result, &pos);
	mu_check(is_success);
	mu_check((result.type == ELEMENT_INT));
	mu_check((pos == input + 8));
	mu_check((result.as_int == 12345));
	mu_check((*pos == '\0'));
	
	input = "   -12345";
	pos = input;
	is_success = parse_element(&result, &pos);
	mu_check(is_success);
	mu_check((result.type == ELEMENT_INT));
	mu_check((pos == input + 9));
	mu_check((result.as_int == -12345));
	mu_check((*pos == '\0'));

	input = "\"ABCD\"";
	pos = input;
	is_success = parse_element(&result, &pos);
	mu_check(is_success);
	mu_check((result.type == ELEMENT_STRING));
	mu_check((pos == input + 6));
	mu_check(strcmp(result.as_string, "\"ABCD\""));
	mu_check((*pos == '\0'));

	free_element(result);

	mu_end();

}

int _test_parse_element_invalid() { // Tests invalid parse_element calls
	mu_start();

	Element result;
	char* input = "A12345";
	char* pos = input;
	bool is_success = parse_element(&result, &pos);
	mu_check(!is_success);
	mu_check((pos == input));
	mu_check((*pos == 'A'));

	input = "ABCD\"";
	pos = input;
	is_success = parse_element(&result, &pos);
	mu_check(!is_success);
	mu_check((pos == input));
	mu_check((*pos == 'A'));

	mu_end();

}

int _test_print_element() { // Tests print_element
	mu_start();

	Element* element = malloc(sizeof(*element));
	*element = (Element) { .type = ELEMENT_INT, .as_int = 0};
	printf("0 = ");
	print_element(*element);
	printf("\n");

	element->as_int = 1234;
	printf("1234 = ");
	print_element(*element);
	printf("\n");
	
	element->as_int = -1234;
	printf("-1234 = ");
	print_element(*element);
	printf("\n");

	element->type = ELEMENT_STRING;
	element->as_string = "ABCD";
	printf("ABCD = ");
	print_element(*element);
	printf("\n");

	element->as_string = "abc\\";
	printf("abc\\ = ");
	print_element(*element);
	printf("\n");

	free(element);

	mu_end();
}

int _test_parse_list_valid() {
	mu_start();

	Element* element = malloc(sizeof(*element));
	char* input = "[]";
	char* pos = input;
	bool is_success = parse_element(element, &pos);
	mu_check(is_success);
	mu_check((element->type == ELEMENT_LIST));
	mu_check((pos == input + 2));
	mu_check((*pos == '\0'));
	print_element(*element);
	free(element);

	element = malloc(sizeof(*element));
	input = "[123]";
	pos = input;
	is_success = parse_element(element, &pos);
	mu_check(is_success);
	mu_check((element->type == ELEMENT_LIST));
	mu_check((pos == input + 5));
	mu_check((*pos == '\0'));
	print_element(*element);

	free_element(*element);
	free(element);

	element = malloc(sizeof(*element));
	input = "[123,\"ABC\"]";
	pos = input;
	is_success = parse_element(element, &pos);
	mu_check(is_success);
	mu_check((element->type == ELEMENT_LIST));
	mu_check((pos == input + 11));
	mu_check((*pos == '\0'));
	print_element(*element);

	free_element(*element);
	free(element);

	element = malloc(sizeof(*element));
	input = "[[123, \"ABC\"], 123]";
	pos = input;
	is_success = parse_element(element, &pos);
	mu_check(is_success);
	mu_check((element->type == ELEMENT_LIST));
	mu_check((pos == input + 19));
	mu_check((*pos == '\0'));
	print_element(*element);

	free_element(*element);
	free(element);

	mu_end();
}

int _test_parse_list_invalid() {
	mu_start();

	Element* element = malloc(sizeof(*element));
	char* input = "[,]";
	char* pos = input;
	bool is_success = parse_element(element, &pos);
	mu_check(!is_success);
	mu_check((*pos == ','));
	mu_check((pos == input + 1));
	free_element(*element);
	free(element);

	element = malloc(sizeof(*element));
	input = "[123,A]";
	pos = input;
	is_success = parse_element(element, &pos);
	mu_check(!is_success);
	mu_check((*pos == 'A')); 
	mu_check((pos == input + 5));
	free_element(*element);
	free(element);
	
	element = malloc(sizeof(*element));
	input = "[123,456";
	pos = input;
	is_success = parse_element(element, &pos);
	mu_check(!is_success);
	mu_check((*pos == '\0'));
	free_element(*element);
	free(element);

	mu_end();
}

int main(int argc, char* argv[]) {
	
	mu_run(_test_parse_int_valid);
	mu_run(_test_parse_int_invalid);
	mu_run(_test_parse_element_valid);
	mu_run(_test_parse_element_invalid);
	mu_run(_test_parse_string_valid);
	mu_run(_test_parse_string_invalid);
	mu_run(_test_print_element);
	mu_run(_test_parse_list_valid);
	mu_run(_test_parse_list_invalid);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
