#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)

# Export PYTHONPATH to include the build directory
export PYTHONPATH="$SCRIPT_DIR/build:$PYTHONPATH"
echo "Python path = ${PYTHONPATH}"

echo "Activating virtual environment..."
source "$SCRIPT_DIR/venv/bin/activate"

# Add alias for mkf to the shell
echo "Adding 'mkf' alias for convenient build commands..."
PYBIND11_DIR=$(python3 -m pybind11 --cmakedir)
alias mkf="cd $SCRIPT_DIR/build && cmake -Dpybind11_DIR=${PYBIND11_DIR} .. && make && cd $SCRIPT_DIR"

echo "Adding 'mk_clean' alias for convenient cmake & make clean..."
alias mk_clean="cd $SCRIPT_DIR/build && cmake --build ./ --target clean && make clean"

cd $SCRIPT_DIR
echo "Environment set up. Aliases and PYTHONPATH are active for this session."