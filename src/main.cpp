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
	int status; //returns status of process
	
    int i = 0; //increment index
    int numconnect = 0; //counts connectors in command line.
    bool runnext = true; //checks if its ok to run the next command
    queue<string> connectors; //stores the connectors
    queue<string> comms; //stores the commands
    
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
	    bool execSuccess = true; //checks if command runs correctly
	    i = 0;
	    if(comms.empty()) //comms should always have commands if not then it breaks out of the loop
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
                if (runnext == false) //ignores the next command because of connectors conditionals
                {
                    comms.pop();
                }
                else //points char array to a command
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
                connectors.push(comms.front()); //store connector
                comms.pop(); //remove connector from queue
                //cout << "Current connector: " << connectors.front() << endl;
                break; //exit loop: the char array has the full command loaded
        	}
        	// double connecctors ; ; or ; && or && || should error out
        }
        array[i] = '\0'; //null terminate
        // for(unsigned k = 0; array[k] != '\0'; k++)
        // {
        //     cout << "Pointer " << k << ": "; 
        //     cout << array[k];
        //     cout << endl;
        // }
        string ex = "exit"; //checks for exit
        if ((comms.empty()) && (!connectors.empty())) 
        {
            cout << "command ends on a connector\n";
            break;
        }
        else if(array[0] == NULL) //if there are two connectors in a row then a[0] is most likely null
        {
            cout << "Double connectors \n";
            break;
        }
        if (array[0] == ex) // checks if user enters exit command
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
            status = execvp(array[0], array);
            execSuccess = false;
            perror("There was an error with the executable or argument list");
        }
        if (processID > 0)
        {
        	if((pid = wait(&status)) < 0) //checks for failure
        	{
        		perror("Process failed");
        		exit(-1);
        	}
        	if (execSuccess == true) //execvp succeeded
        	{
        	    //cout << "Command worked\n";
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
        	            cout << "Invalid, ended with a connector\n";
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
        	        
        	        if (comms.empty())
        	        {
        	            break;
        	        }
        	        runnext = false;
        	        connectors.pop();
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
        	//cout << "Parent: finished\n" << endl;
        }
	}
}
int main (int argc, char **argv)
{
    //size_t len = 300;
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
        string cmd;
        cout << user << "@" << host <<"$ ";
        getline(cin, cmd);
        parsing(cmd);
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
        executecmd(b);
        cout << "Executing done\n";
    }
    free (host);
    return 0;
}
