#include "response.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char* readFile(char *fileName) {
	// create the file pointer
	FILE* file = fopen(fileName, "r");

	if (file == NULL) {
		return NULL;
	}

	// move the file pointer to EOF
	fseek(file, 0, SEEK_END);
	int fSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	// allocating heap to use outside of current function scope
	char *readBytes = malloc(sizeof(char) * (fSize + 1));

	// FILE -> strin
	size_t bytesRead = fread(readBytes, 1, fSize, file);

	fclose(file);

	// null terminator, otherwise more bytes may be read that are not part of the template
	readBytes[bytesRead] = '\0';

	return readBytes;
}
