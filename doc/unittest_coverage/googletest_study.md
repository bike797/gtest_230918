[[home]](./README.md) / [[root]](../README.md)
===

# Google Test 설치 방법  
googletest 소스 다운로드  
```
$ wget https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
$ tar xvf v1.14.0.tar.gz
$ rm v1.14.0.tar.gz
$ mv googletest-1.14.0/ googletest
```
1. 동적 라이브러리
 - libgtest.so

2. 정적 라이브러리 - *
 - libgtest.a

구글 테스트용 라이브러리 빌드 (설치 환경이 다른경우 라이브러리 재빌드 필요)  
`setup.bat` 파일을 이용하여 `gtest-all.o gtest_main.o`을 포함하는 `libgtest.a`라는 이름의 정적 라이브러리를 생성  

`setup.bat`는 다음 내용을 포함합니다.  
 - Google Test의 실행을 위해 main 함수가 작성되어야 합니다.  
 - Google Test Framework에서는 다양한 환경에서 동작하는 기본적인 main 함수를 제공합니다.  
   - gtest_main.cc, gmock_main.cc 등  
   - 라이브러리에 *_main을 포함시키면, 매번 main을 작성할 필요가 없습니다.  
 - `setup.bat` 는 main을 포함하도록 빌드합니다. 
  - gtest-all.cc gmock-all.cc gmock_main.cc 포함  
  - TEST의 sepc 를 표시하기 위한 매크를 gtest.h 코드에 포함하였음  
    `#define SPEC(msg) printf("[ SPEC     ] %s\n", msg)`


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
