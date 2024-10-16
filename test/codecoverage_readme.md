# Code coverage  

코드 Unit test coverage test를 위하여 오픈 소스인 GCOVR을 활용함  

참고 사이트  
- pypi.org: https://pypi.org/project/gcovr/  
- 코드 커버리지 오픈소스 git hub: https://github.com/gcovr/gcovr/  
- 코드 커버리지 적용 방법: https://int-i.github.io/cpp/2021-08-14/cpp-codecov/#google_vignette
  
## 코드 커버리지 설치(오픈소스)  
gcover 설치  

```
pip install gcovr
```

## 분석을 위한 코드 컴파일시 Flag 적용  
`--coverage` flag 적용
    ```
    g++ --coverage example.cpp -o example
     ```
  - `--coverage` 는 `-fprofile-arcs`  `-ftest-coverage`과 동일합니다.  
  - -O0 은 GCC 컴파일러의 최적화 기본 값입니다.  
`CMakeList.txt` 에 적용  

  ```
  option(ENABLE_COVERAGE "Enable coverage" OFF)

  if(ENABLE_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
  endif()
  ```
  주의: `add_link_options`는 CMake 3.13이상에서 동작합니다.

## Cmake 설정 및 빌드  

      ```
      $ cmake -S . -B build -DENABLE_COVERAGE=ON
      $ cmake --build build
      ```

## 빌드된 바이너리 실행  
   ```
   $ ./example
   ```

## 코드 커버리지 보고서 생성  

코드 실행이 완료되면 `.gcda`와 `.gcno` 파일이 생성됩니다.  
위 파일을 Gcov를 통해 분석하면 코드 커버리지 보고서를 얻을 수 있습니다.  
Gcovr는 Gcov를 쉽게 사용할 수 있게 만든 도구입니다.  

```
gcovr -r $ROOT_PATH -f $SRC_PATH --html-details -o $OUTPUT_PATH/coverage.html
```

output path에서 `coverage.html` 보고서 확인


참고: vs-code 에서 [`ms-vscode.live-server`](https://marketplace.visualstudio.com/items?itemName=ms-vscode.live-server) extention 을 설치하면 에디터에서 html 파일 볼수 있음 
