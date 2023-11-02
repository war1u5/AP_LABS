#!/bin/bash

for file in *.txt; do
    rm "$file"
    echo "Deleted $file"
done