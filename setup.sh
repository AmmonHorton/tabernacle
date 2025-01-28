#!/bin/bash

# Exit immediately if a command fails
set -e

# Determine the directory where the setup.sh script is located
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)

echo "=== Setting up the Tabernacle environment ==="

# Check for Python 3
if ! command -v python3 &> /dev/null; then
    echo "Error: Python 3 is not installed. Please install it and try again."
    exit 1
fi

# Check for pip
if ! command -v pip3 &> /dev/null; then
    echo "Error: pip3 is not installed. Please install it and try again."
    exit 1
fi

# Check for CMake
if ! command -v cmake &> /dev/null; then
    echo "Error: CMake is not installed. Installing..."
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        sudo apt update && sudo apt install -y cmake
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        brew install cmake
    else
        echo "Unsupported OS. Please install CMake manually."
        exit 1
    fi
fi

# Check for g++ or clang++
if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
    echo "Error: A C++ compiler (g++ or clang++) is not installed. Please install one and try again."
    exit 1
fi

# Create and activate Python virtual environment
if [ ! -d "$SCRIPT_DIR/venv" ]; then
    echo "Creating Python virtual environment..."
    python3 -m venv "$SCRIPT_DIR/venv"
fi

echo "Activating virtual environment..."
source "$SCRIPT_DIR/venv/bin/activate"

# Install Python dependencies
echo "Installing Python dependencies..."
pip install --upgrade pip
pip install -r "$SCRIPT_DIR/requirements.txt"

# Generate CMakeLists.txt
echo "Generating CMakeLists.txt..."
cat <<EOL > "$SCRIPT_DIR/CMakeLists.txt"
cmake_minimum_required(VERSION 3.10)
project(Tabernacle)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Pybind11
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

# Include directories
include_directories(\${Python3_INCLUDE_DIRS})

# Source files
file(GLOB SOURCES "${SCRIPT_DIR}/src/cpp/*.cc")

# Shared library target
pybind11_add_module(bible_bindings \${SOURCES})

# Link libraries
target_link_libraries(bible_bindings PRIVATE Python3::Python)

# Add custom iOS build target if on macOS
if(\${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_custom_target(build_ios ALL
        COMMAND \${CMAKE_COMMAND} -E echo "Building iOS app using Buildozer..."
        COMMAND buildozer init
        COMMAND buildozer -v ios debug
        WORKING_DIRECTORY \${CMAKE_SOURCE_DIR}
        COMMENT "Build the iOS app"
    )
endif()
EOL

echo "CMakeLists.txt created successfully."

# Build the project using CMake
echo "Building the project..."
mkdir -p "$SCRIPT_DIR/build"
cd "$SCRIPT_DIR/build"

# Explicitly set the pybind11 directory
PYBIND11_DIR=$(python3 -m pybind11 --cmakedir)
cmake -Dpybind11_DIR=${PYBIND11_DIR} ..
make

# Move back to the project root
cd "$SCRIPT_DIR"

# Final message
echo "=== Setup Complete ==="
echo "The project has been built successfully!"
echo "Activate your virtual environment with 'source env.sh'"
