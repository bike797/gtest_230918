#!/bin/sh
g++ $@ -std=c++14 -I ./googletest/googletest/include -L. -lgtest -pthread
