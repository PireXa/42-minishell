//
// Created by fde-albe on 9/27/22.
//

#ifndef UNTITLED_QUOTES_H
#define UNTITLED_QUOTES_H
#define BUFFER_SIZE 10

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct  s_fds
{
    char    *cmd;
    struct s_fds    *next;
}               t_fds;

#endif //UNTITLED_QUOTES_H
