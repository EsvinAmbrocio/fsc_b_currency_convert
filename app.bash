#!/bin/bash

# Function to display help
function display_help() {
    echo "Usage: $0 <filename.c>"
    echo "Example: $0 my_program.c"
    echo ""
    echo "This script compiles a C file to a binary using Docker, runs it, and then removes the container and the binary."
}

# Validate the number of arguments
if [ $# -ne 1 ]; then
    display_help
    exit 1
fi

# Get the filename
filename="$1"
filename_without_extension="${filename%.*}"

if [ ! -f "$filename" ] || [ ! "${filename##*.}" == "c" ]; then
    # El archivo no existe o no tiene extensión .c
    echo "El archivo '$filename' no es válido."
    exit 1
fi

# Compile the C file to a binary
if ! docker run -it --net=host --rm --workdir=/home -v $PWD:/home gcc:13.2 gcc -o "$filename_without_extension" "$filename"; then
    exit 1
fi

# Run the binary
./"$filename_without_extension"

# Delete the binary
rm -f "$filename_without_extension"

