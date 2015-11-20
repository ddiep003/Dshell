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
#include <sys/stat.h>
//system libraries end
#include <csignal>
#include <queue>
#include "rshell.h"
#include "test.h"

//when i hit a connector in char array set it to null and keep track of array

int main (int argc, char **argv)
{
    string user; //user name
    char* host = (char*)malloc(300); //host name
    if (getlogin() != NULL) 
    {
        user = getlogin();
    }
    else 
    {
        perror("Error with getting user");
    }
    if (gethostname(host, 300) == -1) 
    {
        perror("Error with getting host name");
    }
    //cout << host << endl;
    while (true)
    {
        BEGINNING:
        string cmd;
        string test = "test";
        string bracket = "[";
        cout << user << "@" << host <<"$ ";
        getline(cin, cmd);
        parsing(cmd);
        if(AreParenBal(cmd) == false)
        {
            perror("Parenthesis not balanced\n");
            goto BEGINNING;
        }
        char* b[MEMORY]; //character array that stores commands
        char command[MEMORY]; //char array that holds the converted command
        //cout << "Copying \n";
        for(unsigned i =0; cmd[i] != '\0'; i++)
        {
            command[i] = cmd[i];
        }
        command[cmd.length()] = '\0';
        for (unsigned i = 0; command[i] != '\0'; i++) //outputs user input 
        {
            cout << command[i];
        }
        cout << endl;
        commandsort(command, b);
        queue<string> connectors;
        cout << "Executing commands\n";
        executecmd(b, connectors);
        cout << "Executing done\n";
        
        
    }
    free (host);
    return 0;
}
