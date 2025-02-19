# WordFrequencyChecker
## About the Project

WordFrequencyChecker is a C project that demonstrates the implementation of different search techniques in lists and hashmaps. The goal is to analyze the performance of each method when counting word frequencies in text files. Currently, only Linear Search is implemented, while Binary Search and Hash Table are still under development.

This project is useful for those who want to study and compare different search approaches in data structures.

## Development Status

✅ Linear Search - Implemented and functional

❌ Binary Search - In progress

❌ Hash Table - In progress

## License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0). This means you are free to use, modify, and distribute it, as long as you comply with the same licensing terms.
Compilation and Execution

## Requirements

- GCC (C Compiler)
- Make (to simplify compilation)

## How to Compile

Clone the repository or copy the files to a local directory.

Open a terminal, navigate to the project directory, and run:

```sh
make
```

This will create the executable in the bin/ folder under the name WordFrequencyChecker.

## How to Run

After compiling, you can run the program with the following command:

```sh
bin/WordFrequencyChecker -f <file_path>
```

## Available options:

--help                     -h                   Display available commands

--file <path>              -f <path>            (Required) Specify the text file to analyze

--mode <linear (Default)>  -m <linear>          (Optional) Choose the search method (linear, binary, hashmap)

## Example usage:

```sh
bin/WordFrequencyChecker -f bin/largeText.txt -m linear
```
## Contribution

Since the project is still under development, contributions are welcome! If you would like to help implement Binary Search or Hash Table, feel free to open issues or pull requests.
