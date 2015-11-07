#!/bin/bash

cd ..
cd bin
(echo "echo hel #lo" 
echo "exit") | ./rshell #-good
(echo "echo hello#"
echo "exit") | ./rshell # -good
(echo "ls #-a"
echo "exit") | ./rshell  #-good
(echo "ls ; pwd ; echo hello # ; ls ; pwd; uname"
echo "exit") | ./rshell #-good