#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

// Function that escapes special characters in a given input string meant for a shell command.
char* encode_shell_string(const char* str) {
    size_t len = strlen(str);
    char* escaped_str = malloc(len * 2 + 1); // allocate space for the escaped string

    if (escaped_str == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    size_t i, j;
    for (i = 0, j = 0; i < len; i++) {
        if (str[i] == '\'' || str[i] == '\\') {
            escaped_str[j++] = '\\';
        }
        escaped_str[j++] = str[i];
    }
    escaped_str[j] = '\0';

    return escaped_str;
}

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) { 
        fprintf(stderr, "Please provide the address of a file as an input.\n");
        return -1;
    }
    char cmd[BUFSIZE] = "wc -c < ";
    char* escaped_str = encode_shell_string(argv[1]);
    strncat(cmd, escaped_str, BUFSIZE - 9);
    free(escaped_str);
    system(cmd);
}
