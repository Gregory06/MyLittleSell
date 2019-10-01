//
// Created by Greg Postnikoff on 28.10.18.
//

#ifndef MICROSHA_STRING_FUNCS_H
#define MICROSHA_STRING_FUNCS_H

#define BUFSIZE 1024

char *read_line(void)
{
    int bufsize = BUFSIZE;
    int position = 0;
    char *buffer = (char*)malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF) {
            exit(EXIT_SUCCESS);
        } else if (c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += BUFSIZE;
            buffer = (char*)realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

#define TOK_BUFSIZE 10
#define TOK_DELIM "|"

char **split_for_coveyor(char *line, int *PipeQuan) {
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = (char**)malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup;

    if (!tokens) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < strlen(line); i++)
        if (line[i] == '|')
            (*PipeQuan)++;

    token = strtok(line, TOK_DELIM);
//    printf("%p", token);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = (char**)realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                free(tokens_backup);
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

char **process_meta(char **cmd, int PipeQuan) {
    for(int i = 0; i < PipeQuan; i++) {

    }
}

#undef TOK_DELIM
#undef BUFSIZE
#define BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"


char **split_line(char *line)
{
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = (char**)malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup;

    if (!tokens) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = (char**)realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                free(tokens_backup);
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

#define DIR_NAME_SIZE 100

void revers(char *str) {
    char * str1 = (char *) calloc(DIR_NAME_SIZE, sizeof(char));
    int ptr = 0;
    for (int i = 0; i < DIR_NAME_SIZE; i++)
        if (str[DIR_NAME_SIZE - 1 - i] != 0)
            str1[ptr++] = str[DIR_NAME_SIZE - 1 - i];

    strcpy(str, str1);
}

char *get_dir_name(char * full_name) {
    char * dir_name = (char *) calloc(DIR_NAME_SIZE, sizeof(char));
    int ptr = 0;
    for (int i = (int) strlen(full_name); i > 0; i--) {
        if (full_name[i] != '/')
            dir_name[ptr++] = full_name[i];
        else {
            revers(dir_name);
            return dir_name;
        }
    }
}


#endif //MICROSHA_STRING_FUNCS_H
