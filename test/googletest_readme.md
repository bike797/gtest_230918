# Basic C++ Unit Testing with GTest, CMake, and Submodules  
  출처 :  https://dev.to/tythos/basic-c-unit-testing-with-gtest-cmake-and-submodules-4767  

## git submodules 
 - git 프로젝트 그대로 작업 프로젝트의 하위 모듈로 사용 할 수 있음  
    참고 : https://git-scm.com/book/en/v2/Git-Tools-Submodules  
 - 개발 프로젝트의 커밋과 submodule 의 커밋 히스트리는 독립적인 프로젝트와 같이 적용됨  


## 내 프로젝트에 sub module 방식으로 googletest를 적용하는 방법  

  - 프로젝트내 test/ 폴더 생성  
    - 테스트 파일(또는 모듈)이 반드시 프로젝트 소스의 일부가 아니라는 것을 투명하게 표시하는 것이 도움이 됨  
    - 개발자와 CMake 모두에게 정적 라이브러리에 대해 이러한 테스트를 빌드/링크하고 있으며 소스 자체가 아니라는 것을 명확히 하는 데 도움이 됨  
  - gooletest를 서브모듈로 추가      
    ```
    git submodule add https://github.com/google/googletest.git
    git submodule update --init --recursive
    ```
    
    . --init: 서브모듈이 아직 초기화되지 않은 경우, 해당 서브모듈을 초기화합니다. 즉, 서브모듈의 Git 저장소를 클론하여 로컬에 생성합니다.  
    . --recursive: 서브모듈이 또 다른 서브모듈을 포함하고 있는 경우, 이 옵션을 사용하면 모든 하위 서브모듈도 재귀적으로 초기화하고 업데이트합니다.  
    
    프로젝트를 처음 로컬로 다운 받은 경우  
    submodule의 소스를 업데이트할 필요가 있는 경우  
    해당 경로에 파일이 존재하지 않는 경우  
    `git submodule update --init --recursive` 명령을 실행한다.  
  - cmake 파일에서 종속성을 연결하고 구성  
    ```
    # hook and configure dependencies
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(googletest EXCLUDE_FROM_ALL)
    enable_testing()
    ```
    . gtest_force_shared_crt: 이 변수는 Google Test(GTest) 라이브러리를 빌드할 때 공유 CRT(C Runtime Library)를 사용하도록 강제합니다.  
    . ON: 이 값을 설정하여 공유 CRT를 사용하도록 지정합니다.  
    . CACHE BOOL "" FORCE: 이 부분은 CMake의 캐시에서 이 값을 강제로 설정하겠다는 의미입니다. 즉, 이전에 설정된 값이 있더라도 무시하고 이 값을 사용합니다.  
    . add_subdirectory(googletest EXCLUDE_FROM_ALL):  
    . add_subdirectory: 이 명령은 지정된 하위 디렉토리(여기서는 googletest)를 현재 CMake 프로젝트에 추가합니다.  
    . EXCLUDE_FROM_ALL: 이 옵션은 해당 하위 디렉토리의 타겟이 기본적으로 빌드되지 않도록 설정합니다. 즉, 이 디렉토리의 타겟을 명시적으로 빌드할 때만 포함됩니다.  
    . enable_testing(): 이 명령은 CMake에서 테스트를 활성화합니다. 이를 통해 CMake는 테스트를 정의하고 실행할 수 있는 기능을 제공합니다.  
  - 이것은 내부에서 한 번만 설정하면 되며 CMakeLists.txt, 이후에는 각 테스트 모듈을 하나씩 추가할 수 있습니다.  
  - 각 테스트 모듈에 대한 새로운 컴파일 대상을 정의 하고 자체 프로젝트의 실행 파일로 추가
    ```
    # add; link; and catalog test_hello tests
    add_executable(test_defaults tests/test_defaults.cpp)
    target_include_directories(test_defaults PUBLIC ${CMAKE_SOURCE_DIR})
    target_link_libraries(test_defaults gtest gtest_main ${PROJECT_NAME})
    add_test(NAME test_defaults COMMAND test_defaults)
    ```
  - Make 프로젝트는 "tests/" 폴더에서 정적 라이브러리와 연관된 단위 테스트를 모두 빌드합니다.   
    빌드가 완료되면 실행 파일이 생성되어야 하는 "build/" 폴더에서 이러한 테스트(해당 라이브러리에 링크됨)를 실행할 수 있습니다.  
    이제 간단한 일련의 표준 CMake 명령으로 최종 결과를 볼 수 있는 지점에 도달했습니다.  
    ```cmd
    # windows 환경에서 cmake 실행의 예시
    cmake -S . -B build
    cmake --build build
    build\\Debug\\test_defaults.txt
    ```
    . -S: 소스 디렉토리를 지정합니다.  
    . -B: 빌드 디렉토리를 지정합니다.  
    .는 현재 디렉토리를 의미하며, build는 생성될 빌드 디렉토리의 이름입니다.  
    . --build build: build 디렉토리에서 실제로 빌드를 수행합니다.  
    CMake가 생성한 빌드 시스템(예: Makefile, Visual Studio 솔루션 등)을 사용하여 프로젝트를 컴파일하고 링크합니다.  
  - `test_defaults.exe` 실행 후 모든 것이 잘 진행된다면 gtest가 완료된 것입니다.
  
  [Home](./readme.md)
