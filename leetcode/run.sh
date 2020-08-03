#!/bin/sh
dir=$1
fileName=$2
fileNameWithoutExt=$3
var=${dir%/*}
DIR=${var##*/}
rm -rf $dir/../build
mkdir $dir/../build
g++ -DDIR=$DIR -std=c++17 $dir/$fileName -I $dir/../ -o $dir/../build/$fileNameWithoutExt -l gtest -l gtest_main -l pthread
$dir/../build/$fileNameWithoutExt