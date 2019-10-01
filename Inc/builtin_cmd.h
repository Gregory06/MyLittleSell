//
// Created by Greg Postnikoff on 29.10.18.
//

#ifndef MICROSHA_BUILTIN_CMD_H
#define MICROSHA_BUILTIN_CMD_H

int cd(char **args);
int pwd(char **args);
int time(char **args);
int exit(char ** args);


char *builtin_str[] = {
        "cd",
        "pwd",
        "time",
        "exit"
};

int (*builtin_func[]) (char **) = {
        &cd,
        &pwd,
        &time,
        &exit
};


int cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }
//    printf("hi");
    return 1;
}


int pwd(char **args)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);

    return 1;
}
//###########################################
//###########################################
//###########################################
//###########################################

#include "string_funcs.h"
time_t user_begin, user_end, sys_begin, sys_end;

int launch_time(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        user_end = time(NULL);
        printf("%d\n", (int) user_end);
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("lsh");
    } else {
        sys_begin = time(NULL);
        printf("hiii\n");
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        sys_end = time(NULL);
    }

    return 1;
}


int exit(char **args)
{
    return 0;
}



int timee(char **args)
{
    user_begin = time(NULL);
    sleep(1);
    int status = launch_time(args+1);
    printf("%lf\n", (double) user_begin);
    printf("%lf\n", (double) user_end);
    printf("%lf\n", (double) sys_begin);
    printf("%lf\n", (double) sys_end);
    printf("%lf %ld\n", (double) user_begin - (double) user_end , (long int) (sys_end - sys_begin));
    return status;
}

//###########################################
//###########################################
//###########################################
//###########################################

#endif //MICROSHA_BUILTIN_CMD_H
