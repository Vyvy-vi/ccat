#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "stdbool.h"

#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];


struct cmdFlags {
	bool number;
	bool blankOmitNumber;
};

void read_stdin2_stdout() {
	while (1) {
		size_t cnt = fread(&buffer, sizeof(char), BUFFER_SIZE - 1, stdin);
		buffer[cnt] = '\0';
		fwrite(buffer, sizeof(char), cnt, stdout);
		fflush(stdout);
		buffer[0] = '\0';
			
		if (cnt < BUFFER_SIZE - 1 && feof(stdin)) break;
	}

}

void readFile2_stdout(char* filename, struct cmdFlags flags) {
	FILE* filePtr = fopen(filename, "r");

	while (!feof(filePtr)) {
		size_t cnt = fread(&buffer, sizeof(char), BUFFER_SIZE - 1, filePtr);
		buffer[cnt] = '\0';
		printf("%s", buffer);
		buffer[0] = '\0';		
	}

	fclose(filePtr);
}


int main(int argc, char **argv) {
	if (argc == 1) {
		read_stdin2_stdout();
	} else {
		struct cmdFlags flags = {false, false};
		int argIndex = 1;

		while (argIndex < argc) {
			char* arg = argv[argIndex];
			if (arg[0] != '-') break;
			else if (arg[1] == 'n') flags.number = true;
			else if (arg[1] == 'b') flags.blankOmitNumber = true;
			argIndex++;
		}
		
		while (argIndex < argc) {
			readFile2_stdout(argv[argIndex], flags);
			argIndex++;
		}
	}
}
