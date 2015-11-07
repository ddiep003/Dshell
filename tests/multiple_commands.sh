#!/bin/bash

cd ..
cd bin
(echo "ls ; ls ; pwd && echo hello ; exit") | ./rshell #ls ls pwd hello exit -good
(echo "ls || ls; pwd || echo hello ; exit") | ./rshell #ls pwd exit          -good
(echo "ls && ls; pwd && echo hello ; exit") | ./rshell #ls ls pwd hello exit -good
(echo "ls -a ; ls -ssxw && pwd && echo hello ; exit") | ./rshell #ls -a exit -good
(echo "ls && ls || pwd || echo hello ; exit") | ./rshell # ls ls hello exit -good
(echo "ls -sfwefwef && ls || pwd ; echo hello ; exit") | ./rshell #pwd hello exit -bad ls runs regardless