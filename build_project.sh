#!/bin/bash

# Check if the user provided a folder name as input
if [ $# -ne 1 ]; then
    echo "Usage: $0 <folder_name>"
    exit 1
fi

# Get the folder name from command line argument
folder_name=$1

# Create build directory
build_dir="${folder_name}build"
mkdir -p $build_dir

# Navigate to the specified folder
cd $folder_name || exit 1

# Run CMake
echo "Running CMake..."
cmake -B "../$build_dir"

# Navigate back to the original directory
cd ..

# Build the project using make
echo "Building the project..."
make -C $build_dir

echo "Build completed. Executable is located in: ./$build_dir"
