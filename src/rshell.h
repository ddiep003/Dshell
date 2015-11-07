#ifndef RSHELL_H
#define RSHELL_H


#define MEMORY 66666
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
}
#endif