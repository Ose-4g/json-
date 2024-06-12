#!/bin/bash

cmake -S . -B build
cd build && make

if [[ $# > 0 && "$1" == "t" ]]
then 
   ctest
else
    ./jsonpp
fi

cd ..