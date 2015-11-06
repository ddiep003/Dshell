#ifndef RSHELL_H
#define RSHELL_H


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
}
#endif