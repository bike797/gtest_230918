#!/bin/sh

ROOT_PATH=..
SRC_PATH=${ROOT_PATH}/dev/src
OUTPUT_PATH=${ROOT_PATH}/test/gcovr_report

if [ -d "$OUTPUT_PATH" ]; then
    rm -rf $OUTPUT_PATH
fi
mkdir $OUTPUT_PATH

#gcovr -r $ROOT_PATH/test/build -b --exclude-unreachable-branches --exclude-throw-branches -f $SRC_PATH --html --html-details -o ./gcovr/index.html
gcovr -r $ROOT_PATH -f $SRC_PATH --html-details -o $OUTPUT_PATH/coverage.html
