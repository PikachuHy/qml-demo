#!/bin/sh
dir=$1
fileName=$2
fileNameWithoutExt=$3
var=${dir%/*}
DIR=${var##*/}
SOLUTION_FILE="${DIR}/${fileName}"
TEST_FILE="${DIR}/test.cpp"
DIR_FILENAME="${DIR}_${fileNameWithoutExt}"
rm -rf $dir/../build
mkdir $dir/../build
g++ -DDIR_FILENAME=$DIR_FILENAME -DSOLUTION_FILE=${SOLUTION_FILE} -DTEST_FILE=${TEST_FILE} -std=c++17 $dir/../main.cpp \
-I $dir/../ -o $dir/../build/$fileNameWithoutExt -l gtest -l gtest_main -l pthread
$dir/../build/$fileNameWithoutExt