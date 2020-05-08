#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	FILE *fp;
	int c;

	fp = fopen("woods", "r");
	while(1) {
		c = fgetc(fp);
		if (feof(fp)) {
			break;
		}
		if (c=='\n') {
			printf("we have newline char");		
		}else{
			printf("char: %c\n", c);	
		}
	}	
}
