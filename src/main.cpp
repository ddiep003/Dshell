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
#include "rshell.h"


//when i hit a connector in char array set it to null and keep track of array
void executecmd(char* array[])
{
    pid_t processID, pid; //processID = commands
	int status;
	
    int i = 0;
    int numconnect = 0; //counts connectors in command line.
    bool runnext = true; //checks if its ok to run the next command
    queue<string> connectors;
    queue<string> comms;
    
	while(array[i] != '\0')
	{
	    comms.push(array[i]); //pushes commands into queue
	    if ((comms.front() == ";") || (comms.front() == "&&") ||
	       (comms.front() == "||"))
	       {
	           numconnect = numconnect + 1;
	       }
	    array[i] = '\0'; //refreshes the array
	    i++;
	}
	while (true)
	{
	    int j = 0;
	    while(array[j] != '\0')
	    {
    	    array[j] = '\0'; //refreshes the array
    	    j++;
	    }
	    bool execSuccess = true;
	    i = 0;
	    if(comms.empty())
	    {
	        break;
	    }
        while (true)
        {
            if(comms.empty())
            {
                break;
            }
            if ((comms.front() != ";") && (comms.front() != "&&") && //populate array
        	    (comms.front() != "||"))
            {
                if (runnext == false)
                {
                    comms.pop();
                }
                else
                {
                    char* temp = new char [100];
                    strcpy(temp, comms.front().c_str());
                    array[i] = temp;
                    comms.pop();
                    i++;
                }
            }
            else //comms.front == connector //stop parsing and execvp
            {
                connectors.push(comms.front());
                comms.pop();
                cout << "Current connector: " << connectors.front() << endl;
                break;
        	}
        	// double connecctors ; ; or ; && or && || should error out
        }
        array[i] = '\0';
        for(unsigned k = 0; array[k] != '\0'; k++)
        {
            cout << "Pointer " << k << ": "; 
            cout << array[k];
            cout << endl;
        }
        string ex = "exit";
        if (!connectors.empty())
        {
            
        }
        else if(array[0] == NULL)
        {
            cout << "Double connecctors \n";
            break;
        }
        else if (array[0] == ex)
        {
            cout << "Exiting\n";
            exit(0);
        }
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
            cout << "Work dammit \n";
            status = execvp(array[0], array);
            cout << "Execute failed \n";
            execSuccess = false;
            perror("There was an error with the executable or argument list");
        }
        if (processID > 0)
        {
        	if((pid = wait(&status)) < 0)
        	{
        	    cout << "Process failed\n";
        		perror("Process failed");
        		exit(-1);
        	}
        	if (execSuccess == true)
        	{
        	    cout << "Command worked\n";
        	    if (connectors.empty())
        	    {
        	        break;
        	    }
        	    if (connectors.front() == "&&")
        	    {
        	        if (comms.empty())
        	        {
        	            cout << "Invalid, ended with a connector\n";
        	            exit(-1);
        	        }
        	        connectors.pop();
        	        runnext = true;
        	    }
        	    else if (connectors.front() == ";")
        	    {
        	        connectors.pop();
        	        runnext = true;
        	    }
        	    else if (connectors.front() == "||")
        	    {
        	        if (comms.empty())
        	        {
        	            cout << "No more commands\n";
        	            connectors.pop();
        	            break;
        	        }
        	        connectors.pop();
        	        runnext = false;
        	   }
        	}
        	else if (execSuccess == false)
        	{
        	    if(connectors.empty())
        	    {
        	        break;
        	    }
        	    if (connectors.front() == "&&")
        	    {
        	        runnext = false;
        	        if (comms.empty())
        	        {
        	            break;
        	        }
        	    }
        	    else if (connectors.front() == ";")
        	    {
        	        connectors.pop();
        	        runnext = true;
        	    }
        	    else if (connectors.front() == "||")
        	    {
        	        connectors.pop();
        	        runnext = true;
        	    }
        	    
        	}
        	cout << "Parent: finished\n" << endl;
        }
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