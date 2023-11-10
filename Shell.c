#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "Shell.h"
#include "StringVector.h"

void shell_init(struct Shell *s) {
    s->running = 0;
    s->line_number = 0;
    s->buffer_size = 0;
    s->buffer = malloc(10 * sizeof(struct StringVector));
}

void shell_run(struct Shell *s) {
    s->running = 1;
    
    while (s->running) {
        
        printf("\e[32mpaulo\e[0m@\e[34mmyshell\e[0m:\e[33m%s\e[0m $ ", getcwd(NULL, 0));
        fflush(stdout);

        shell_execute_line(s);
        
    }
    return;
}

void shell_free(struct Shell *s){
    for (int i = 0; i < (int)( s->buffer_size ); i++) {
        string_vector_free(&s->buffer[i]);
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
    }
    else if(strcmp(args, "help") == 0) {
        printf("Tapez exit pour arrêter.\n");
            
    }
    else if (strcmp(args, "cd") == 0)
    {
        if (cmd_line.size == 1) {
            chdir(getenv("HOME"));
        }
        else {
            char * argv = string_vector_get(&cmd_line, 1);
            if (chdir(argv) != 0) {
                printf("Erreur lors du changement de répertoire.\n");
            }
        }
    }
    else if (strcmp(args, "!")== 0) {
        if (cmd_line.size == 1) {
            system(getenv("SHELL"));
        }
        else {
            system(strjoinarray(cmd, &cmd_line, 1, cmd_line.size, " "));
        }
    }
    else if (strcmp(args, "cmds") == 0) {
        for (int i = 0; i < (int)( s->buffer_size ); i++) {
            printf("%d: %s\n", i, &s->buffer[i]);
        }
    }
    else {
        printf("Commande inconnue.\n");
    }
    shell_buffering(s, &cmd_line);
}

void shell_buffering(struct Shell *s, struct StringVector *cmd_line){
    if (s->buffer_size > 0) {
        string_vector_free(&s->buffer[s->buffer_size - 1]);
        for (int i = s->buffer_size; i > 0; i--) {
            s->buffer[i] = s->buffer[i-1];
        }
    }
    s->buffer[0] = *cmd_line;
    s->buffer_size++;
}

int main(int argc, char** argv)
{
    struct Shell shell;
    shell_init(& shell);
    shell_run(& shell);
    shell_free(& shell);
    return (EXIT_SUCCESS);
}