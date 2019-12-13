#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents the root of a trie
node *root;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // create traversal pointer
        node *traverse = root;

        // iterate through the key's (word) letters
        for (int i = 0; i < strlen(word); i++)
        {
            // assuming all letters are lowercase...
            int index = word[i] - 96;

            // apostrophes in the dictionary are causing a memory disaster, index -57 "~~~aaaaaahhhhh!"
            // avoiding the appostrophe memory catastrophe
            if (index == -57)
            {
                // make appostrophe fit into index 27 so they can be cleared.
                index = 27;
            }

            if (traverse->children[index] == NULL)
            {
                // create new node
                node *newNode = malloc(sizeof(node));
                newNode->is_word = false;
                for (int j = 0; j < N; j++)
                {
                    newNode->children[j] = NULL;
                }
                traverse->children[index] = newNode;
                traverse = newNode;
            }
            else
            {
                traverse = traverse->children[index];
            }
        }

        // end of word, mark this node's is_word as true
        traverse->is_word = true;
    }

    // Close dictionary
    fclose(file);
    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return traverseToCount(root);
}

unsigned int traverseToCount(node *traverse)
{
    int count = 0;
    if (traverse->is_word)
    {
        count++;
    }
    for (int index = 0; index < N; index++)
    {
        if (traverse->children[index] != NULL)
        {
            count += traverseToCount(traverse->children[index]);
        }
    }
    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *traverse = root;

    for (int i = 0; i < strlen(word); i++)
    {
        int index = tolower(word[i]) - 96;

        // avoiding the apostrophe memory catastrophe!!
        if (index == -57)
        {
            index = 27;
        }

        if (traverse->children[index] == NULL)
        {
            return false;
        }
        else
        {
            traverse = traverse->children[index];
        }
    }
    return traverse->is_word;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    return traverseToDestroy(root);
}

bool traverseToDestroy(node *traverse)
{
    for (int index = 0; index < N; index++)
    {
        if (traverse->children[index] != NULL)
        {
            traverseToDestroy(traverse->children[index]);
        }
    }
    free(traverse);
    return true;
}
