#include "../include/textTools.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to normalize text by converting all letters to lowercase
// and replacing punctuation with spaces.
char *normalizeText(const char *text) {
    size_t len = strlen(text);
    char  *normalizedText = calloc(len + 1, sizeof(char)); // Allocate memory for the normalized text

    if (!normalizedText) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Iterate through each character in the text
    for (size_t i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            normalizedText[i] = tolower(text[i]); // Convert letters to lowercase
        } else if (isspace(text[i])) {
            normalizedText[i] = text[i];  // Keep spaces unchanged
        } else {
            normalizedText[i] = ' ';  // Replace punctuation and special characters with spaces
        }
    }

    return normalizedText;
}

// Function to split a text into individual words based on spaces and new lines.
char **splitTextInWords(const char *text, size_t *wordCount) {
    const char *delimiters = " \n\t";  // Define word separators
    char       *textCopy   = strdup(text);  // Create a mutable copy of the text
    if (!textCopy) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Count the number of words in the text
    size_t count = 0;
    char  *word  = strtok(textCopy, delimiters);
    while (word) {
        count++;
        word = strtok(NULL, delimiters);
    }

    // Allocate memory for the list of words
    char **wordsList = calloc(count + 1, sizeof(char *));
    if (!wordsList) {
        fprintf(stderr, "Memory allocation failed\n");
        free(textCopy);
        exit(1);
    }

    // Restore the text copy and extract words again
    strcpy(textCopy, text);
    word       = strtok(textCopy, delimiters);
    size_t idx = 0;
    while (word) {
        wordsList[idx] = strdup(word);  // Allocate and store each word
        if (!wordsList[idx]) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        idx++;
        word = strtok(NULL, delimiters);
    }

    wordsList[idx] = NULL;   // Null-terminate the list of words
    *wordCount     = count;  // Return the word count

    free(textCopy);  // Free the copied text used for tokenization

    return wordsList;
}

// Function to free the allocated memory for the word list
void freeWordsList(char **wordsList) {
    if (wordsList == NULL) {
        return; 
    }
    
    for (size_t i = 0; wordsList[i] != NULL; i++) {
        free(wordsList[i]); // Free each word
    }
    free(wordsList); // Free the word list array
}

