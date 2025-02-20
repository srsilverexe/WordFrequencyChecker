#!/bin/bash

# Directory to texts files to be analised
dir="texts"

# Get all .txt files in the folder
for file in "$dir"/*.txt; do
  # Get only the file name
  filename=$(basename "$file")
  echo "Analised file: $filename" | tee output.txt
  # Run the program to analise;
  time ./bin/WordFrequencyChecker -f "$file" | tee output.txt

done

echo "Output exported to output.txt"

