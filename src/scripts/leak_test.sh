#!/bin/bash

TEST_NAME="../../../build/unittest"

if [[ "$(uname)" == "Linux" ]]; then
    valgrind --tool=memcheck --leak-check=yes --log-file="leak_log.log" ./$TEST_NAME
elif [[ "$(uname)" == "Darwin" ]]; then
    leaks -atExit -- ./$TEST_NAME
fi