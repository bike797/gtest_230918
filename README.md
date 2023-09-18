# Google Test 설치 방법
1. 동적 라이브러리
 - libgtest.so

2. 정적 라이브러리 - *
 - libgtest.a
```
$ wget https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
$ tar xvf v1.14.0.tar.gz
$ rm v1.14.0.tar.gz
$ mv googletest-1.14.0/ googletest
```

```
# gtest-all.cc
$ g++ -c ./googletest/googletest/src/gtest-all.cc -I ./googletest/googletest/include -I ./googletest/googletest/ -std=c++14

# gtest_main.cc
$ g++ -c ./googletest/googletest/src/gtest_main.cc -I ./googletest/googletest/include -std=c++14

# libgtest.a
$ ar rcv libgtest.a gtest-all.o gtest_main.o
```
