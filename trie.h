#include "array.h"
typedef struct FffTrie_ {
        FffArray content;
} FffTrie;
void fffTrieInit(FffTrie *trie);
void fffTrieDestroy(FffTrie *trie);
void fffTrieInsert(char *string);
void fffTrieRemove(char *string);
size_t fffTrieLookUp(size_t previousKey,char newChar);
