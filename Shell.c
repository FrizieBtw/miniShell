#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "Shell.h"
#include "StringVector.h"

void shell_init(struct Shell *s) {
    s->running = 0;
    s->line_number = 0;
    s->buffer_size = 0;
    s->buffer = malloc(10 * sizeof(struct StringVector));
    s->pwd = "~";
}

void shell_run(struct Shell *s) {
    s->running = 1;
    
    while (s->running) {
        
        printf("\e[32mpaulo\e[0m@\e[34mmyshell\e[0m:\e[33m%s\e[0m $ ", s->pwd);
        fflush(stdout);

        shell_execute_line(s);
        
    }
    return ( EXIT_SUCCESS );
}

void shell_free(struct Shell *s){
    for (int i = 0; i < (int)( s->buffer_size ); i++) {
        free(s->buffer[i]);
    }
    free(s->buffer);
}

void shell_execute_line(struct Shell *s){
    char cmd[256];
    int size = read(STDIN_FILENO, cmd, 256);
    cmd[size] = '\0';
    struct StringVector cmd_line = split_line(cmd);
    char * args = string_vector_get(&cmd_line, 0);
    if (strcmp(args, "exit") == 0) {
            s->running = 0;
            string_vector_free(&cmd_line);
        }
        else if(strcmp(args, "help") == 0) {
            printf("Tapez exit pour arrêter.\n");
            string_vector_free(&cmd_line);
        }
        else if (strcmp(args, "cd") == 0)
        {
            if (cmd_line.size == 1) {
                chdir(getenv("HOME"));
                
            }
            char * argv = string_vector_get(&cmd_line, 1);
        }
        
        else {
            printf("Commande inconnue.\n");
            string_vector_free(&cmd_line);
        }
}

int main(int argc, char** argv)
{
    struct Shell shell;
    shell_init(& shell);
    shell_run(& shell);
    shell_free(& shell);
    return (EXIT_SUCCESS);
}