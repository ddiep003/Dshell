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

#define MEMORY 66666
using namespace std;
void parsing(string& cmd)
{
    char* parsed = (char*) malloc (MEMORY);
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
// queue of strings
//pop strings to an array of char
//point array to c
void commandsort(char* cmd, char* b[] )
{
    int i = 0;
    char* token = strtok(cmd, " ");
    while (token != NULL)
    {
        b[i] = token;
        token = strtok(NULL , " " );
        i++;
    }

    b[i] = '\0';
    //cout << "Work\n";
    // queue<string> test;
    // for(unsigned k = 0; b[k] != '\0'; k++)
    // {
    //     cout << "Pointer " << k << ": "; 
    //     for(unsigned l = 0; b[k][l] != '\0'; l++)
    //     {
    //         cout << b[k][l];
    //     }
    //     test.push(b[k]);
    //     cout << endl;
    // }
}


//when i hit a connector in char array set it to null and keep track of array
void executecmd(char* array[])
{
    pid_t processID, pid; //processID = commands
	int status;
    int i = 0;
    queue<string> connectors;
    queue<string> comms;
    
	while(array[i] != '\0')
	{
	    comms.push(array[i]); //pushes commands into queue
	    i++;
	}
	i = 0;

	//char* temp = new char [100];    //mem = 66666
    while (true)
    {
	    //char* temp[100];
        if(comms.empty())
        {
            break;
        }
        if ((comms.front() != ";") || (comms.front() != "&&")|| //populate array
    	    (comms.front() != "||"))
        {
            char* temp = new char [100];
            strcpy(temp, comms.front().c_str());
            array[i] = temp;
            comms.pop();
            i++;
        }
        else //comms.front == connector //stop parsing and execvp
        {
            connectors.push(comms.front());
            comms.pop();
            break;
    	}
    }
    

    array[i] = '\0';
    for(unsigned k = 0; array[k] != '\0'; k++)
    {
        cout << "Pointer " << k << ": "; 
        cout << array[k];
        // for(unsigned l = 0; array[k][l] != '\0'; l++)
        // {
        //     cout << array[k][l];
        // }
        cout << endl;
    }
    cout << "Value of i: " << i <<endl;
    processID = fork(); //fork
    if(processID < 0) //fork fails
    {
    	cout << "Fork Failed" << endl;
        exit(1);
    }
    else if(processID == 0) // child process
    {
        cout << "Executing \n";
        cout << "Child: executing: \n";
        //cout << comms.front() << endl; // switches off the parent
        cout << "Work dammit \n";
        execvp(array[0], array);
        cout << "Execute failed \n";
        perror("There was an error with the executable or argument list");
    }
    else if (processID > 0)
    {
    	if((pid = wait(&status)) < 0)
    	{
    	    cout << "Process failed\n";
    		perror("Process failed");
    		exit(-1);
    	}
    	if (WIFEXITED(status))
    	{
    		if(WIFEXITED(status) != 0)
    		{
    		    //bool success = false;
    		}
    	}
        
    	cout << "Parent: finished" << endl;
    }
	
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
    char* b[MEMORY];
    char command[MEMORY];
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
    executecmd(b);
    //character pointer array
    //char *b[MEMORY];
    //if i find a space ' ' then everything before that space goes into the first pointer
    //of the character array get the address of everything before the space into the chararray
    
    
}
// if it fails then child returns -1 //
//perror outputs failure when fork fails
//waitpid(current_pid, &status, 0)


//strtok(string, " ");
//while (string != NULL)