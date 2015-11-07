# Linux Shell for CS100
# By Danny Diep
## Shell Functions

rshell is a c++ shell that emulates unix and bash. For now, there is only basic shell functions. This includes:

* A command prompt
* Command recognition
* Connector recognition
* Comment recognition
* Exit function
* User and host computer recognition

Using multiple functions is possible.

## ls
During runtime, you can ls by typing:

``ls ``

You can also add optional parameters, such as the -a, -l, or -R flags. 

``ls -a -l -R ``


##How to use
You can compile rshell and ls with:

``make``

##Prerequisites

* C++ Compiler
* SDL Library
* Bash Terminal

##Bugs
Future bugs will be documented here.

* In main.cpp, sometimes inappropriate flags are ran by execvp regardless.
* In main.cpp, booleans for connectors seem to work most effectively with failed valid commands.
* In scripts,  invalid input as the first command causes infinite looping. Does not occur when run normally.
* In main.cpp, when a command fails the next one might run twice.
* In main.cpp, nonsense commands do not trigger connectors
* In tests,    all commands end with exit to facilitate running multiple at once
* In rshell,   as long as user enters proper commands there won't be any problems.
* In rshell,   the program includes some but not all idiot checks.

##Limitations
Limitations of rshell.

* Any command over 66,666 characters will overflow the command buffer.

Limitations of ls.
