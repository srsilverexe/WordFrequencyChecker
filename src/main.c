#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "../include/item.h"
#include "../include/linearSearch.h"
#include "../include/binarySearch.h"
#include "../include/textTools.h"

// Enum to represent different search methods
typedef enum { MODE_LINEAR,
               MODE_BINARY,
               MODE_HASH_TABLE } searchMethod;

// Function declarations
void      printHelp(void);
u_int64_t getFileSize(FILE *file);
void      linearMode(Item **itemList, size_t *itemListSize, char **wordsList, const size_t wordsListSize);
void      binaryMode(Item **itemList, size_t *itemListSize, char **wordsList, const size_t wordsListSize);


int main(int argc, char *argv[]) {
    char        **filePathList = malloc(sizeof(char*) * (argc - 2));
    size_t         filePathListSize = 0;
    searchMethod mode     = MODE_LINEAR;

    // Check if any parameters were passed
    if (argc == 1) {
        printf("No parameters were passed\n");
        exit(1);
    } else {
        for (size_t i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
                printHelp();
                exit(1);
            } else if (strcmp(argv[i], "--file") == 0 || strcmp(argv[i], "-f") == 0) {
                if (i + 1 >= argc) {
                    printf("No file specified\n");
                    free(filePathList);
                    exit(1);
                }
                
                while ((i + 1 < argc) && (argv[i + 1][0] != '-')) {
                    filePathList[filePathListSize ++] = argv[++i];  // Get the next argument as file path
                }
            } else if (strcmp(argv[i], "--mode") == 0 || strcmp(argv[i], "-m") == 0) {
                if (i + 1 >= argc) {
                    printf("No mode specified\n");
                    exit(1);
                }
                char *normalizedText = normalizeText(argv[++i]);  // Normalize the input text

                // Set the search mode based on the argument passed
                if (strcmp(normalizedText, "linear") == 0) {
                    mode = MODE_LINEAR;
                } else if (strcmp(normalizedText, "binary") == 0) {
                    mode = MODE_BINARY;
                } else if (strcmp(normalizedText, "hashmap") == 0) {
                    mode = MODE_HASH_TABLE;
                } else {
                    printf("Invalid mode specified\n");
                    free(normalizedText);
                    exit(1);
                }
                free(normalizedText);
            }
        }
    }
    
    u_int64_t fullNumberOfWords = 0;

    for (size_t filePathIdx = 0; filePathIdx < filePathListSize; filePathIdx ++) {
        printf("Current file: %s\n", filePathList[filePathIdx]);

        // Open the file for reading
        FILE *file = fopen(filePathList[filePathIdx], "r");
        if (file == NULL) {
            fprintf(stderr, "Could not open file: %s\n", filePathList[filePathIdx]);
            exit(1);
        }

        
        // Get the file size
        u_int64_t fileSize = getFileSize(file);
        if (fileSize <= 0) {
            fprintf(stderr, "The specified file is empty\n");
            fclose(file);
            exit(1);
        }

        // Allocate memory for the file content
        char *text = malloc(fileSize + 1);
        if (text == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            fclose(file);
            exit(1);
        }

        // Read file content into memory
        fread(text, 1, fileSize, file);
        text[fileSize] = '\0';
        fclose(file);

        // Normalize the text content
        char *normalized = normalizeText(text);

        // Split the text into words
        size_t wordsListSize = 0;
        char **wordsList     = splitTextInWords(normalized, &wordsListSize);

        // Choose the processing method based on the mode selected
        if (mode == MODE_HASH_TABLE) {
            // Hash table mode (to be implemented)
        } else {
            // Allocate initial space for items
            Item  *items         = calloc(10, sizeof(Item));
            size_t itemsListSize = 10;

            if (mode == MODE_LINEAR) {
                linearMode(&items, &itemsListSize, wordsList, wordsListSize);
            } else {  // MODE_BINARY
                binaryMode(&items, &itemsListSize, wordsList, wordsListSize);
            }

            // Find the most repeated word
            fullNumberOfWords += wordsListSize;
            printf("Total number of words: %zu\n", wordsListSize);
            qsort(items, itemsListSize, sizeof(Item), compareItemsByValue);
            printf("Most repeated word: %-15s\tRepeat Times: %-5i\n", items[0].key, items[0].value);

            // Free allocated memory
            free(items);
        }

        freeWordsList(wordsList);
        free(text);
        free(normalized);
    }

    printf("Total of files analised: %zu\n", filePathListSize);
    printf("Total of words analised: %zu\n", fullNumberOfWords);
    

    free(filePathList);

    return 0;
}

// Prints help information about the available command-line options
void printHelp(void) {
    printf(
        "--help                     -h                   Print all commands\n"
        "--file <path>              -f <path>            (Required) Specify the file to process\n"
        "--mode <linear (Default)>  -m <linear (Default)> (Optional) Choose search method\n"
        "        binary                 binary\n"
        "        hashmap                hashmap\n");
}

// Determines the size of a file
u_int64_t getFileSize(FILE *file) {
    fseek(file, 0, SEEK_END);
    u_int64_t fileSize = ftell(file);
    rewind(file);
    return fileSize;
}

void linearMode(Item** itemList, size_t* itemListSize, char** wordsList, const size_t wordsListSize) {
    for (size_t wordListIdx = 0; wordListIdx < wordsListSize; wordListIdx++) {
        // Search if the current word already exists in the items array using a linear search.
        Item* searchedItem = linearSearch(*itemList, *itemListSize, wordsList[wordListIdx]);
        if (searchedItem == NULL) { // If the word is not found...
            bool inserted = false;
            
            // Try to find an empty slot (i.e., where key == NULL) in the current array.
            for (size_t i = 0; i < *itemListSize; i++) {
                if ((*itemList)[i].key == NULL) {
                    (*itemList)[i].key = strdup(wordsList[wordListIdx]);
                    (*itemList)[i].value = 1;
                    inserted = true;
                    break;
                }
            }
            
            // If no empty slot is available, reallocate the array with additional space.
            if (!inserted) {
                size_t newSize = *itemListSize + 10;
                // Allocate a new array with the increased size.
                Item* newItemList = calloc(newSize, sizeof(Item));
                if (newItemList == NULL) {
                    perror("calloc failed");
                    exit(EXIT_FAILURE);
                }
                
                // Copy the existing items into the new array.
                for (size_t i = 0; i < *itemListSize; i++) {
                    if ((*itemList)[i].key != NULL) {
                        newItemList[i].key = strdup((*itemList)[i].key);
                        newItemList[i].value = (*itemList)[i].value;
                        free((*itemList)[i].key);
                    } else {
                        newItemList[i].key = NULL;
                        newItemList[i].value = 0;
                    }
                }
                
                // Free the old array and update the pointer and its size.
                free(*itemList);
                *itemList = newItemList;
                *itemListSize = newSize;
                
                // Insert the new word into the first available slot in the resized array.
                for (size_t i = 0; i < *itemListSize; i++) {
                    if ((*itemList)[i].key == NULL) {
                        (*itemList)[i].key = strdup(wordsList[wordListIdx]);
                        (*itemList)[i].value = 1;
                        break;
                    }
                }
            }
        } else {
            // If the word is already present in the array, increment its occurrence count.
            searchedItem->value++;
        }
    }
}

void binaryMode(Item **itemList, size_t *itemListSize, char **wordsList, const size_t wordsListSize) {
    for (size_t wordListIdx = 0; wordListIdx < wordsListSize; wordListIdx++) {
        // Search if the current word already exists in the items array using a binary search.
        Item* searchedItem = binarySearch(*itemList, *itemListSize, wordsList[wordListIdx]);
        if (searchedItem == NULL) { // If the word is not found...
            bool inserted = false;
            
            // Try to find an empty slot (i.e., where key == NULL) in the current array.
            for (size_t i = 0; i < *itemListSize; i++) {
                if ((*itemList)[i].key == NULL) {
                    (*itemList)[i].key = strdup(wordsList[wordListIdx]);
                    (*itemList)[i].value = 1;
                    inserted = true;
                    break;
                }
            }
            
            // If no empty slot is available, reallocate the array with additional space.
            if (!inserted) {
                size_t newSize = *itemListSize + 10;
                // Allocate a new array with the increased size.
                Item* newItemList = calloc(newSize, sizeof(Item));
                if (newItemList == NULL) {
                    perror("calloc failed");
                    exit(EXIT_FAILURE);
                }
                
                // Copy the existing items into the new array.
                for (size_t i = 0; i < *itemListSize; i++) {
                    if ((*itemList)[i].key != NULL) {
                        newItemList[i].key = strdup((*itemList)[i].key);
                        newItemList[i].value = (*itemList)[i].value;
                        free((*itemList)[i].key);
                    } else {
                        newItemList[i].key = NULL;
                        newItemList[i].value = 0;
                    }
                }
                
                // Free the old array and update the pointer and its size.
                free(*itemList);
                *itemList = newItemList;
                *itemListSize = newSize;
                
                // Insert the new word into the first available slot in the resized array.
                for (size_t i = 0; i < *itemListSize; i++) {
                    if ((*itemList)[i].key == NULL) {
                        (*itemList)[i].key = strdup(wordsList[wordListIdx]);
                        (*itemList)[i].value = 1;
                        break;
                    }
                }
                qsort(*itemList, *itemListSize, sizeof(Item), compareItemsByKey);
            }
        } else {
            // If the word is already present in the array, increment its occurrence count.
            searchedItem->value++;
        }
    }

}
