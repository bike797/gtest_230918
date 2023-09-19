#!/bin/sh
g++ $@ -std=c++14 -I ./googletest/googletest/include \
-I ./googletest/googlemock/include \
-L. -lgtest -pthread
