@echo off
SET PATH_HOME_GOOGLETEST=.\googletest

echo ### libgtes.a 라이브러리 생성
echo ### 빌드 후 생성된 lib 경로  %PATH_HOME_GOOGLETEST%\lib


echo ### Google Test에서는 main을 아래 형태로 제공해야 합니다.
echo ###  - Google Test는 다양한 환경에서 동작하는 main을 제공합니다.
echo ###    gtest_main.cc, gmock_main.cc 등
echo ###  - 라이브러리에 *_main을 포함시키면, 매번 main을 작성할 필요가 없습니다.
echo ###
echo ### 현재 라이브러리는 main을 포함하도록 빌드함
echo ### gtest-all.cc gmock-all.cc gmock_main.cc 포함
echo ###
echo ### 참고: TEST의 sepc 를 표시하기 위한 매크를 gtest.h 코드에 포함하였음
echo ###       #define SPEC(msg) printf("[ SPEC     ] %s\n", msg)

REM if NOT EXIST %PATH_HOME_GOOGLETEST%\lib
if not exist "%PATH_HOME_GOOGLETEST%\lib" (
    mkdir "%PATH_HOME_GOOGLETEST%\lib"
)

echo $ build gtest-all
g++ -o %PATH_HOME_GOOGLETEST%/lib/gtest-all.o -c %PATH_HOME_GOOGLETEST%/googletest/src/gtest-all.cc -I %PATH_HOME_GOOGLETEST%/googletest/include -I %PATH_HOME_GOOGLETEST%/googletest/ -std=c++14
echo $ build gmock-all
g++ -o %PATH_HOME_GOOGLETEST%/lib/gmock-all.o -c %PATH_HOME_GOOGLETEST%/googlemock/src/gmock-all.cc -I %PATH_HOME_GOOGLETEST%/googlemock/include -I %PATH_HOME_GOOGLETEST%/googlemock -I %PATH_HOME_GOOGLETEST%/googletest/include -std=c++14
echo $ build gmock_main
g++ -o %PATH_HOME_GOOGLETEST%/lib/gmock_main.o -c %PATH_HOME_GOOGLETEST%/googlemock/src/gmock_main.cc -I %PATH_HOME_GOOGLETEST%/googlemock/include -I %PATH_HOME_GOOGLETEST%/googletest/include -std=c++14

echo $ create libgtest.a
ar rcv %PATH_HOME_GOOGLETEST%/lib/libgtest.a %PATH_HOME_GOOGLETEST%/lib/gtest-all.o %PATH_HOME_GOOGLETEST%/lib/gmock-all.o %PATH_HOME_GOOGLETEST%/lib/gmock_main.o > %PATH_HOME_GOOGLETEST%/lib/log.o

del %PATH_HOME_GOOGLETEST%\lib\*.o

echo ### end