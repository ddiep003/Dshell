#!/bin/bash

cd ..
cd bin
(echo "ls"
echo "ls -a"
echo "ls -l"
echo "pwd"
echo "hostname"
echo "echo hello"
echo "echo my name is danny diep"
echo "uname"
echo "exit") | ./rshell



