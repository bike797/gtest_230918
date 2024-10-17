[[home]](./README.md) / [[root]](../README.md)
===

# Code coverage  

코드 Unit test coverage test를 위하여 오픈 소스인 GCOVR을 활용함  

참고 사이트  
- pypi.org: https://pypi.org/project/gcovr/  
- 코드 커버리지 오픈소스 git hub: https://github.com/gcovr/gcovr/  
- 코드 커버리지 적용 방법: https://int-i.github.io/cpp/2021-08-14/cpp-codecov/#google_vignette
  
## 코드 커버리지 보고서 생성 도구 설치(오픈소스)  
`.gcda`와 `.gcno` 분석을 위한 gcover 설치  
해당 파일을 Gcov를 사용하여 분석하면 코드 커버리지 보고서를 얻을 수 있습니다.  
Gcovr는 Gcov를 쉽게 사용할 수 있게 만든 도구입니다.

```
pip install gcovr
```

## 분석을 위해 코드 컴파일 flag 적용  
`--coverage` flag 적용
    ```
    g++ --coverage example.cpp -o example
     ```
  - `--coverage` 는 `-fprofile-arcs`  `-ftest-coverage`과 동일합니다.  
  - -O0 은 GCC 컴파일러의 최적화 기본 값입니다.  

  ```
  ### CMakeList.txt 에 컴파일 flag 옵션 적용  

  option(ENABLE_COVERAGE "Enable coverage" OFF)

  if(ENABLE_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
  endif()
  ```
  주의: `add_link_options`는 CMake 3.13이상에서 동작합니다.

## Cmake 설정 및 빌드  
컴파일시 코드 커리리지 정보를 추가하려면 `-DENABLE_COVERAGE=ON` 옵션을 선택합니다.
  ```
  $ cmake -S . -B build -DENABLE_COVERAGE=ON
  $ cmake --build build
  ```

## 빌드된 바이너리 실행  
커버리지 분석을 위해 빌드된 바이너리 코드를 실행합니다. 
   ```
   $ ./example
   ```

## 코드 커버리지 보고서 생성  

코드 실행이 완료되면 `.gcda`와 `.gcno` 파일이 생성됩니다.  
gcovr를 사용하여 커버리지 보고서를 생성합니다.  

```
gcovr -r $ROOT_PATH -f $SRC_PATH --html-details -o $OUTPUT_PATH/coverage.html
```

output path에서 `coverage.html` 보고서 확인 합니다.

___
참고:     
vscode 에서 [`ms-vscode.live-server`](https://marketplace.visualstudio.com/items?itemName=ms-vscode.live-server) extention 을 설치하면 ssl, wsl 등의 원격 개발 도구 사용 중에 html 문서의 preview 가 가능합니다. (편리함)  
