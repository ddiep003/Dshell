#include <iostream>
//linux system libraries
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
//system libraries end
#include <csignal>
#include <queue>


int main (int argc, char **argv)
{
    //std::cout << "Hello";
    pid_t pid; // integer that can store a process ID (use pid_t for portability)

    if ((pid = fork()) == -1) // system functions also set a variable called "errno"
    {
        perror("fork"); // this function automatically checks "errno"
        // and prints the error plus what you give it
        return EXIT_FAILURE;
    }
// ---- by when you get here there will be two processes
    if (pid == 0) // child process
    {
        // look up exec functions
    }
    else // parent process
    {
    }

    return EXIT_SUCCESS;
    return 0;
}
