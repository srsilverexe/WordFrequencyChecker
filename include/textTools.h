#ifndef TEXT_TOOLS_H
#define TEXT_TOOLS_H

#include <stddef.h>
char  *normalizeText(const char *text);
char **splitTextInWords(const char *text, size_t *wordCount);
void   freeWordsList(char **wordsList);

#endif  // TEXT_TOOLS_H
