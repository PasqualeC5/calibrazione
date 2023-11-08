#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <folder_name>"
    exit 1
fi

# Get the folder name from the command line argument
folder_name="$1"

# Define the build directory name
build_dir="${folder_name}_build"

# Check if the specified folder exists
if [ ! -d "$folder_name" ]; then
    echo "Error: Folder '$folder_name' not found."
    exit 1
fi

# Create the build directory if it doesn't exist
if [ ! -d "$build_dir" ]; then
    mkdir "$build_dir"
fi

# Change directory to the build directory
cd "$build_dir" || exit 1

# Run cmake to generate build files
cmake "../$folder_name"

# Check if cmake command was successful
if [ $? -eq 0 ]; then
    # Run make to build the project
    make
    # Check if make command was successful
    if [ $? -eq 0 ]; then
        echo "Build successful. Executable can be found in ./$build_dir"
    else
        echo "Error: Build failed."
    fi
else
    echo "Error: CMake configuration failed."
fi

# Change back to the original directory
cd ..
