cls
g++ -o gtest.exe %* -std=c++14 -I .\googletest\googletest\include -I .\googletest\googlemock\include -L.\googletest\lib -lgtest -lpthread
gtest.exe
