//
// Created by Greg Postnikoff on 29.10.18.
//

#ifndef MICROSHA_MICROSHA_KERNEL_H
#define MICROSHA_MICROSHA_KERNEL_H


int launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("error");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("error");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}


int execute(char **args)
{
    int i;

    if (args[0] == NULL) {
        return 1;
    }

    for (i = 0; i < 4; i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return launch(args);
}

#include "string_funcs.h"



int runPipedCommands(char** parts, int numPipes) {

    int status;
    int i = 0;
    pid_t pid;
    int part = 0;;

    int pipefds[2*numPipes];

    for(i = 0; i < (numPipes); i++){
        if(pipe(pipefds + i*2) < 0) {
            perror("can't pipe");
            exit(EXIT_FAILURE);
        }
    }


    int j = 0;
    while(parts[part]) {
        pid = fork();
        if(pid == 0) {

            if(parts[part+1]){
                if(dup2(pipefds[j + 1], 1) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            if(j != 0 ){
                if(dup2(pipefds[j-2], 0) < 0){
                    perror(" dup2");///j-2 0 j+1 1
                    exit(EXIT_FAILURE);

                }
            }


            for(i = 0; i < 2*numPipes; i++){
                close(pipefds[i]);
            }

            char ** args = split_line(parts[part]);
            if( execvp(*args, args) < 0 ){
                perror(*args);
                exit(EXIT_FAILURE);
            }
        } else if(pid < 0){
            perror("error");
            exit(EXIT_FAILURE);
        }

        part++;
        j+=2;
    }

    for(i = 0; i < 2 * numPipes; i++){
        close(pipefds[i]);
    }

    for(i = 0; i < numPipes + 1; i++)
        wait(&status);

    return 1;
}


int loop(void)
{
    char *line;
    char **parts;
    char **args;
    int status;
    int PipeQuan = 0;

    int part = 0;

    do {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        char* dir = get_dir_name(cwd);
        printf("%s", dir);

        printf(" > ");

        line = read_line();
        parts = split_for_coveyor(line, &PipeQuan);

        if (PipeQuan) {
            status = runPipedCommands(parts, PipeQuan);
        } else {
            args = split_line(parts[part]);
            status = execute(args);
        }
        free(line);
        free(parts);
        part = 0;
        free(args);
//        printf("%d\n",status);
    } while (status);
}

#endif //MICROSHA_MICROSHA_KERNEL_H
