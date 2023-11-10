#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "StringVector.h"

struct Shell {
    bool running;
    int line_number;
    size_t buffer_size;
    char * buffer;
};

void shell_init(struct Shell *s);
void shell_run(struct Shell *s);
void shell_free(struct Shell *s);
void shell_execute_line(struct Shell *s);
int main(int argc, char** argv);