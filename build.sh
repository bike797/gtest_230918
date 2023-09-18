#!/bin/sh
g++ $1 -std=c++14 -I ./googletest/googletest/include -L. -lgtest -pthread
