#include "trie.h"
void fffTrieInit(FffTrie *trie){
        fffArrayInit(&(trie->content));
        fffArrayExpand(&(trie->content), 1<<CHAR_BIT);
}
