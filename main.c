#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "stdbool.h"
#include "limits.h"

#define BUFFER_SIZE 100

struct cmdFlags {
	bool number;
	bool blankOmitNumber;
};

void read_stdin2_stdout(struct cmdFlags flags) {
	char *line = malloc(LINE_MAX);
	if (line == NULL) {
		printf("Not enough space...");
		return;
	}

	int counter = 0;
	while (fgets(line, LINE_MAX, stdin) != NULL) {
		if (flags.blankOmitNumber) {
			if (line[0] != '\n') {
				counter++;  
				printf("%6d\t%s", counter, line);
			} else {
				printf("%s", line);
			}
		} else if (flags.number) {
			counter++;
			printf("%6d\t%s", counter, line);
		} else {
			printf("%s", line);
		}
		fflush(stdout);
	}
	free(line);
}

void readFile2_stdout(char* filename, struct cmdFlags flags) {
	FILE* filePtr = fopen(filename, "r");

	char *line = malloc(LINE_MAX);
	if (line == NULL) {
		printf("Not enough space...");
		return;
	}

	int counter = 0;
	while (fgets(line, LINE_MAX, filePtr) != NULL) {
		if (flags.blankOmitNumber) {
			if (line[0] != '\n') {
				counter++;  
				printf("%6d\t%s", counter, line);
			} else {
				printf("%s", line);
			}
		} else if (flags.number) {
			counter++;
			printf("%6d\t%s", counter, line);
		} else {
			printf("%s", line);
		}
	}

	free(line);
	fclose(filePtr);
}


int main(int argc, char **argv) {
		
		struct cmdFlags flags = {false, false};
		int argIndex = 1;

		while (argIndex < argc) {
			char* arg = argv[argIndex];
			if (arg[0] != '-') break;
			else if (arg[1] == 'n') flags.number = true;
			else if (arg[1] == 'b') flags.blankOmitNumber = true;
			argIndex++;
		}

		if (argIndex == argc) {
			read_stdin2_stdout(flags);
		}
		
		while (argIndex < argc) {
			readFile2_stdout(argv[argIndex], flags);
			argIndex++;
		}
}
