#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *readFile(const char *path) {
    // Open in binary mode 
    FILE *file = fopen(path, "rb");
    if (file == NULL ) {
        fprintf(stderr, "Cannot open file: %s\n", path);
        exit(74);
    }
    // Get the size in bytes of the file
    fseek(file, 0L, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    // Don't forget 1 byte for the char '\0'
    char* buffer = (char *)malloc(fileSize + 1);
    // Rare error
    if (!buffer) {
        fprintf(stderr, "Out of memory\n");
        fclose(file);
        exit(1);
    }

    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

void readBuffer(char* buffer) {
    int i = 0; 
    while (buffer[i] != '\0'){
        printf("%02x ", (unsigned char)buffer[i++]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(-1);
    }
    char* buffer = readFile(argv[1]);
    readBuffer(buffer);
    return 0;
}
