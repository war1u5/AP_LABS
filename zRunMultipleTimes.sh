#!/bin/bash

if [ "$#" -ne 5 ]; then
    echo "script misusage: $0 <program> <program params: number_of_elems, print_level, number_of_threads> <number of times to be run>"
    exit -1
fi

program="$1"
number_of_elems="$2"
print_level="$3"
number_of_threads="$4"
number_of_times="$5"

for ((i=1; i<=$number_of_times; i++));
do
    result="$($program $number_of_elems $print_level $number_of_threads)"
    echo "run #$i: $result"
done    
