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

## Google Test
```
# gtest-all.cc
$ g++ -c ./googletest/googletest/src/gtest-all.cc -I ./googletest/googletest/include -I ./googletest/googletest/ -std=c++14

# gtest_main.cc
$ g++ -c ./googletest/googletest/src/gtest_main.cc -I ./googletest/googletest/include -std=c++14

# libgtest.a
$ ar rcv libgtest.a gtest-all.o gtest_main.o
```

## Google Test + Google Mock
- Google Mock은 Google Test에 의존성이 있습니다.
```
# gtest-all.cc
$ g++ -c ./googletest/googletest/src/gtest-all.cc -I ./googletest/googletest/include -I ./googletest/googletest/ -std=c++14

# gmock-all.cc
$ g++ -c ./googletest/googlemock/src/gmock-all.cc -I ./googletest/googlemock/include -I ./googletest/googlemock -I ./googletest/googletest/include -std=c++14

# gmock_main.cc
$ g++ -c ./googletest/googlemock/src/gmock_main.cc -I ./googletest/googlemock/include -I ./googletest/googletest/include -std=c++14

# libgtest.a
$ ar rcv libgtest.a gtest-all.o gmock-all.o gmock_main.o

```
