#ifndef RSHELL_H
#define RSHELL_H


#define MEMORY 66666
#include "test.h"
using namespace std;
void parsing(string& cmd) //separates the connectors from the rest of the commands
{
    char* parsed = (char*) malloc (MEMORY);
    for (int i = 0, j = 0; cmd[i] != '\0'; ++i, ++j)
    {
        if(cmd[i] == '#')
        {
            cmd[i] = '\0';
            parsed[j] = '\0';
        }
        else if (cmd[i] == ';')
        {
            parsed[j] = ' ';
            parsed[++j] = ';';
            parsed[++j] = ' ';
        }
        else if (cmd[i] == '|' && cmd[i + 1] == '|')
        {
            parsed[j] = ' ';
            parsed[++j] = '|';
            parsed[++j] = '|';
            parsed[++j] = ' ';
            ++i;
        }
        else if (cmd[i] == '&' && cmd[i + 1] == '&')//&& connector
        {
            parsed[j] = ' ';
            parsed[++j] = '&';
            parsed[++j] = '&';
            parsed[++j] = ' ';
            ++i;
        }
        else if (cmd[i] == '[')
        {
            parsed[j] = ' ';
            parsed[++j] = '[';
            parsed[++j] = ' ';
        }
        else if ((cmd[i] == ']'))
        {
            parsed[j] = ' ';
            parsed[++j] = ']';
            parsed[++j] = ' ';
        }
        else if (cmd[i] == '(')
        {
            parsed[j] = ' ';
            parsed[++j] = '(';
            parsed[++j] = ' ';
        }
        else if (cmd[i] == ')')
        {
            parsed[j] = ' ';
            parsed[++j] = ')';
            parsed[++j] = ' ';
        }
        else
        {
            parsed[j] = cmd[i];
        }
        if (cmd[i + 1] == '\0')
        {
            parsed[j + 1] = '\0';
        }
    }
    cmd = parsed;
    free(parsed); //free memory
}

void commandsort(char* cmd, char* b[]) //sets char array to the command line
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
        for(unsigned k = 0; b[k] != '\0'; k++)
        {
            cout << "Pointer " << k << ": "; 
            cout << b[k];
            cout << endl;
        }
        //cout << "Command sort done\n";
}



void executecmd(char* array[], queue<string> &connectors)
{
    pid_t processID, pid; //processID = commands
	int status; //returns status of process
	string test = "test";
    string bracket = "[";
    queue<string> precedence;
    int i = 0; //increment index
    bool runnext = true; //checks if its ok to run the next command
    //queue<string> connectors; //stores the connectors
    queue<string> comms; //stores the commands
    
	while(array[i] != '\0')
	{
	    comms.push(array[i]); //pushes commands into queue
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
                else if (comms.front() == "(")
                {
                    comms.pop();
                }
                else if (comms.front() == ")")
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
        if((array[0] == test) || (array[0] == bracket))
        {
            //cout << "Running test\n";
            testcommand(array, connectors);
        }
        else
        {
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
}
#endif