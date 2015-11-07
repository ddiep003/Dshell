#!/bin/bash

cd ..
cd bin
(echo "exit") | ./rshell #exits shell -good
(echo "ls; exit") | ./rshell # -good
(echo "ls ; exit && pwd") | ./rshell # -good
(echo "echo hello ; exit && pwd") | ./rshell #-good
(echo "pwd || exit && ls ; exit") | ./rshell #-bad segfaults after pwd
(echo "pwd && exit && ls ; exit") | ./rshell # -good.
(echo "exit && fesxtt") | ./rshell # good
(echo "fester ; exit") | ./rshell # bad -does not exit