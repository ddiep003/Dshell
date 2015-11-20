#ifndef TEST_H
#define TEST_H
#include <sys/stat.h>
#include <sys/types.h>
#include <stack>
using namespace std;

bool IsPair(char opening,char closing)
{
	if(opening == '(' && closing == ')') return true;
	else if(opening == '{' && closing == '}') return true;
	else if(opening == '[' && closing == ']') return true;
	return false;
}
bool AreParenBal(string commands)
{
	stack<char>  checker;
	for(unsigned i =0;i<commands.length();i++)
	{
		if(commands[i] == '(' || commands[i] == '{' || commands[i] == '[')
			checker.push(commands[i]);
		else if(commands[i] == ')' || commands[i] == '}' || commands[i] == ']')
		{
			if(checker.empty() || !IsPair(checker.top(),commands[i]))
				return false;
			else
				checker.pop();
		}
	}
	return checker.empty() ? true:false;
}

bool defaultflag(vector<string>flag)
{
    bool hasE = false;
    for (unsigned i = 0; i <flag.size(); i++)
    {
        if (flag[i] == "-e")
        {
            hasE = true;
        }
    }
    return hasE;
}
bool Dflag(vector<string>flag)
{
    bool hasD = false;
    for (unsigned i = 0; i <flag.size(); i++)
    {
        if (flag[i] == "-d")
        {
            hasD = true;
        }
    }
    return hasD;
}
bool Fflag(vector<string>flag)
{
    bool hasF = false;
    for (unsigned i = 0; i <flag.size(); i++)
    {
        if (flag[i] == "-f")
        {
            hasF = true;
        }
    }
    return hasF;
}

bool testcommand(char* array[], queue <string>& connectors)
{
    int startindex = 1;
    string e = "-e"; //checks exist
    string f = "-f"; //checks if regfile
    string d = "-d"; //check if directory
    vector<string> flag;
    int i = 0;
    while (array[i] != '\0')
    {
        if ((array[startindex] == e) || (array[startindex] == d) 
        || (array[startindex] == f))
        {
            flag.push_back(array[startindex]);
            startindex++;
        }
        else
        {
            i++;
        }
    }
    cout << startindex << endl;
    struct stat filestate;
    if(stat(array[startindex], &filestate)< 0)
    {
        perror("Stat failed\n");
        cout << "Stat failed\n";
        connectors.pop();
        return false;
    }
    else
    {
        cout << "File Exists\n";
        if(Dflag(flag) == true)
        {
            if(S_ISDIR(filestate.st_mode) == true)
            {
                cout << "File is a directory\n";
            }
            else
            {
                cout <<"Not directory\n";
            }
        }
        if(Fflag(flag) == true)
        {
            if (S_ISREG(filestate.st_mode))
            {
                cout << "File is a regular file\n";
            }
            else
            {
                cout << "Not a regular file\n";
            }
        }
        connectors.pop();
        return true;
    }
    
}



#endif