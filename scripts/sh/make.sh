#!/bin/bash

SOURCE=byteorder_test.c
TARGET=byteorder_test
WD=build
SD=test

mkdir -p $WD

platform=$(uname -s)
STATUS=0

gcc -g -Wall -ansi -pedantic -o ${WD}/${TARGET}_gcc.o ${SD}/${TARGET}.c
[ $? -ne 0 ] && STATUS=1

if [[ $platform == Linux ]]; then

    clang -g -Wall -ansi -pedantic -o ${WD}/${TARGET}_clang.o ${SD}/${TARGET}.c
    [ $? -ne 0 ] && STATUS=1

fi

exit $STATUS

