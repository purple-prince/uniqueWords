#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "hash.h"

#define BUFFER_SIZE 1024

// Function prototypes
Hashtable* initializeHashTable();
void processInput(int fileDescriptor, Hashtable* hashTable);
void countUniqueLines(FILE* stream, Hashtable* hashTable);
void cleanupAndExit(Hashtable* hashTable, int fileDescriptor, int exitCode);

int main(int argc, char* argv[]) {
    int fileDescriptor = STDIN_FILENO;
    Hashtable* hashTable = initializeHashTable();

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [file]\n", argv[0]);
        cleanupAndExit(hashTable, -1, EXIT_FAILURE);
    }




    if (argc == 2) {
        fileDescriptor = open(argv[1], O_RDONLY);

        if (fileDescriptor == -1) {

            perror("file opening error");
            cleanupAndExit(hashTable, -1, EXIT_FAILURE);

        }

        FILE* stream = fdopen(fileDescriptor, "r");

        if (!stream) {

            perror("error :()");
            cleanupAndExit(hashTable, fileDescriptor, EXIT_FAILURE);

        }

        countUniqueLines(stream, hashTable);

        fclose(stream);
    } else {

        countUniqueLines(stdin, hashTable);
    }

    cleanupAndExit(hashTable, -1, EXIT_SUCCESS);
}

Hashtable* initializeHashTable() {
    return hash_create();
}

void countUniqueLines(FILE* stream, Hashtable* hashTable) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int uniqueLines = 0;

    while ((read = getline(&line, &len, stream)) != -1) {

        if (!hash_get(hashTable, line)) {

            hash_put(hashTable, strdup(line), 1);
            uniqueLines++;

        }
    }

    free(line);
    printf("%d unique lines\n", uniqueLines);
}

void cleanupAndExit(Hashtable* hashTable, int fileDescriptor, int exitCode) {
    if (hashTable) hash_destroy(hashTable);
    if (fileDescriptor != -1) close(fileDescriptor);
    exit(exitCode);
}
