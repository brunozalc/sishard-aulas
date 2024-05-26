#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *proxima_linha(int fd) {
    char *line = NULL;
    char c;

    while (read(fd, &c, 1) > 0) {
        if (c == '\n') {
            break;
        }

        line = realloc(line, sizeof(char) * (strlen(line) + 2));
        line[strlen(line)] = c;
        line[strlen(line) + 1] = '\0';
    }

    if (line != NULL || strlen(line) > 0) {
        return line;
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    int file = argc > 1 ? open(argv[1], O_RDONLY) : 0;

    if (file < 0) {
        perror("erro ao abrir arquivo");
        return 1;
    }

    char *line;
    while ((line = proxima_linha(file)) != NULL) {
        // se a linha começar com letra maiúscula, imprima-a
        if (line[0] >= 'A' && line[0] <= 'Z') {
            printf("%s\n", line);
        }
        free(line);
    }

    close(file);
    return 0;
}
