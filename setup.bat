g++ -c ./googletest/googletest/src/gtest-all.cc -I ./googletest/googletest/include -I ./googletest/googletest/ -std=c++14
g++ -c ./googletest/googlemock/src/gmock-all.cc -I ./googletest/googlemock/include -I ./googletest/googlemock -I ./googletest/googletest/include -std=c++14
g++ -c ./googletest/googlemock/src/gmock_main.cc -I ./googletest/googlemock/include -I ./googletest/googletest/include -std=c++14
ar rcv libgtest.a gtest-all.o gmock-all.o gmock_main.o