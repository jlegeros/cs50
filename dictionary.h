// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define N 28

typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Prototypes
bool load(const char *dictionary);
unsigned int size(void);
unsigned int traverseToCount(node *travNode);
bool check(const char *word);
bool unload(void);
bool traverseToDestroy(node *traverse);

#endif // DICTIONARY_H
