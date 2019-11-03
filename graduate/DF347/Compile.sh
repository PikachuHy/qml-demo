#!/bin/bash

work_path=$(dirname $0)
cd ./${work_path}

if [ -d "build" ]; then
  rm -rf build
fi

mkdir "build"

cd build || exit

cmake ..

make DF347
