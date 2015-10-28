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
            cout << "made it#" << endl;
            cmd[i] = '\0';
            parsed[j] = '\0';
        }
        else if (cmd[i] == ';')
        {
            cout << "made it;" << endl;
            parsed[j] = ' ';
            parsed[++j] = ';';
            parsed[++j] = ' ';
            display(parsed);
        }
        else if (cmd[i] == '|' && cmd[i + 1] == '|')
        {
            cout << "made it||" << endl;
            parsed[j] = ' ';
            parsed[++j] = '|';
            parsed[++j] = '|';
            parsed[++j] = ' ';
            ++i;
        }
        else if (cmd[i] == '&' && cmd[i + 1] == '&')//&& connector
        {
            cout << "made it&&" << endl;
            parsed[j] = ' ';
            parsed[++j] = '&';
            parsed[++j] = '&';
            parsed[++j] = ' ';
            ++i;
        }
        else if (cmd[i] == '>' && cmd[i + 1] == '>')//stdout redirection append
        {
            parsed[j] = ' ';
            parsed[++j] = '>';
            parsed[++j] = '>';
            parsed[++j] = ' ';
            ++i;
        }
        else if (cmd[i] == '>')//stdout redirection
        {
			parsed[j] = ' ';
			parsed[++j] = '>';
			parsed[++j] = ' ';

        }
        else if (cmd[i] == '<')//stdin redirection
        {
			parsed[j] = ' ';
			parsed[++j] = '<';
			parsed[++j] = ' ';
        }
        else if ((cmd[i] == '0' || cmd[i] == '1' || cmd[i] == '2') &&
				cmd[i + 1] == '>')
        {
            if (cmd[i] == '0')
            {
                parsed[j] = '0';
            }
            else if (cmd[i] == '1') 
            {
                parsed[j] = '1';
            }
            else if (cmd[i] == '2') 
            {
                parsed[j] = '2';
                parsed[++j] = '>';
            }
            if (cmd[i + 2] == '>')
            {
				++i;
				parsed[++j] = '>';
            }
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
        display(parsed);
    }
    cout << "Original " << cmd << endl;
    cout << parsed <<endl;
    display(parsed);
    cmd = parsed;
    cout << "new cmd " << cmd << endl;
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
    cout << cmd << endl;;
    

    
    
}
