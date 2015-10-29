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
void nullconnectors(string& cm)
{
    for(unsigned i = 0; i < cm.size(); ++i)
    {
        if (cm[i] == ';')
        {
            if(cm[i + 1] != '\0')
            {
                cm[i + 1] = '\0';
            }
        }
        if((cm[i] == '&') && (cm[i + 1] == '&'))
        {
            if(cm[i + 2] != '\0')
            {
                cm[i + 2] = '\0';
                //cout << cm[i] << cm[i+1];
            }
        }
        
    } 
}
void commandsort(char* cmd, char* b[] )
{
    int j = 0;
    int k = 0;
    for(unsigned i = 0; cmd[i] != '\0'; i++ )
    {
        if (cmd[i] == ' ')
        {
            b[j] = cmd + k;
            cmd[i] = '\0';
            j++;
            k = i + 1;
        }
        
    }
    b[j + 1] = '\0';
}
int main (int argc, char **argv)
{
    string cmd;
    //while (cmd != "exit")
    //{
        cout << "$ ";
        
        getline(cin, cmd);
        //cout << cmd << endl;
    //}

    parsing(cmd);
    //put null after every connector
    //tokenize strtok with \0 as a delimiter.
    //vector<string> commands;
    
    cout <<"Before nullconnectors: " << cmd << endl;
    //nullconnectors(cmd);
    //cout << *argv <<endl;
    cout <<"After nullconnectors: " <<  cmd << endl;
    char* b[66666];
    vector<char> v(cmd.begin(), cmd.end());
    char* command = &v[0]; // pointer to start of vector
    commandsort(command, b);
    //b[0] = command;
                
    execvp(b[0], b );
    //character pointer array
    //char *b[66666];
    //if i find a space ' ' then everything before that space goes into the first pointer
    //of the character array get the address of everything before the space into the chararray
    
    
}
