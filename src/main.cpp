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

using namespace std;
void display(string x)
{
    for (int i = 0; x[i] != '\0'; ++i)
    {
        cout << x[i];
    }
    cout << endl;
}
void parsing(string& cmd)
{
    char* parsed = (char*) malloc (50000);
    for (int i = 0, j = 0; cmd[i] != '\0'; ++i, ++j)
    {
        if(cmd[i] == '#')
        {
            //cout << "made it#" << endl;
            cmd[i] = '\0';
            parsed[j] = '\0';
        }
        else if (cmd[i] == ';')
        {
            //cout << "made it;" << endl;
            parsed[j] = ' ';
            parsed[++j] = ';';
            parsed[++j] = ' ';
            //display(parsed);
        }
        else if (cmd[i] == '|' && cmd[i + 1] == '|')
        {
            //cout << "made it||" << endl;
            parsed[j] = ' ';
            parsed[++j] = '|';
            parsed[++j] = '|';
            parsed[++j] = ' ';
            ++i;
        }
        else if (cmd[i] == '&' && cmd[i + 1] == '&')//&& connector
        {
            //cout << "made it&&" << endl;
            parsed[j] = ' ';
            parsed[++j] = '&';
            parsed[++j] = '&';
            parsed[++j] = ' ';
            ++i;
        }
        else
        {
            //cout <<"This is parsed at " << parsed[j] << endl;
            parsed[j] = cmd[i];
        }
        if (cmd[i + 1] == '\0')
        {
            parsed[j + 1] = '\0';
            //cout << "Index of j: " << j << end
        }
        //display(parsed);
    }
    cout << "Original: " << cmd << endl;
    cout << "parsed commands: " << parsed <<endl;
    //display(parsed);
    cmd = parsed;
    free(parsed);
    //cout << "new cmd: " << cmd << endl;
    //const char *c = cmd.c_str();
    //strcpy(, parsed);
    //free(parsed)
}

void myFork()
{
	pid_t pid = fork();
	if(pid < 0)
	{
		cout << "Fork Failed" << endl;
		exit(1);
	}
	else if (pid == 0)
	{
		cout << "Child: I'm the child: " << pid << endl;
	}
	else if (pid > 0)
	{
		cout << "Parent: I'm the parent: " << pid << endl;
	}
}
void nullconnectors(string& cm) //finds space ' ' and set it to NULL
{
    for(unsigned i = 0; i < cm.size(); ++i)
    {
        if (cm[i] == ' ')
        {
            cm[i] = '\0';
        }
    } 
}
void commandsort(char* cmd, char* b[] )
{
    int i = 0;
    //cout << "Before the parse\n";
    char* token = strtok(cmd, " ");
    while (token != NULL)
    {
        b[i] = token;
        token = strtok(NULL , " " );
        i++;
    }
    b[i + 1] = '\0';
}
int main (int argc, char **argv)
{
    string cmd;
    cout << "$ ";
    getline(cin, cmd);
    parsing(cmd);
    
    //put null after every connector
    //tokenize strtok with \0 as a delimiter.
    //vector<string> commands;
    char* b[66666];
    char command[66666];
    cout << "Copying \n";
    for(unsigned i =0; cmd[i] != '\0'; i++)
    {
        command[i] = cmd[i];
    }
    command[cmd.length()] = '\0';
    
    for (unsigned i = 0; command[i] != '\0'; i++)
    {
        cout << command[i];
    }
    cout << endl;
    commandsort(command, b);
    for(unsigned i =0; b[i] != '\0'; i++)
    {
        for(unsigned j =0; b[j] != '\0'; j++)
        {
            cout << b[i][j];
        }
        cout << endl;
    }
    
    cout << "Execvp\n";
    execvp(b[0], b );
    //character pointer array
    //char *b[66666];
    //if i find a space ' ' then everything before that space goes into the first pointer
    //of the character array get the address of everything before the space into the chararray
    
    
}
// if it fails then child returns -1 //
//perror outputs failure when fork fails
//waitpid(current_pid, &status, 0)


//strtok(string, " ");
//while (string != NULL)