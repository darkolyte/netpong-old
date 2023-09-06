#!/bin/sh

# Generate build files for Ninja
cmake -B build -G Ninja -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=$BUILD_TYPE

# Check if build files were successfully generated
if [ $? -eq 0 ]
then
    # Build the project
    cd build && ninja
fi