#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <path> <string>"
    exit 1
fi

dir="$1"
search_string="$2"

if [ ! -d "$dir" ]; then
    echo "Error: Directory '$dir' does not exist."
    exit 1
fi

grep -rn --include="*.c" "$search_string" "$dir"

