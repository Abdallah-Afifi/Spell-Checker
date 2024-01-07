#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <string>

struct TrieNode {
    bool endOfWord;
    std::vector<TrieNode*> children;

    TrieNode();

    ~TrieNode();  // Add destructor to handle memory cleanup
};

class trie {
public:
    TrieNode* root;

    trie();

    ~trie();  // Declaration only, definition will be in Trie.cpp

    void insertWord(const std::string& word);

    bool searchWord(const std::string& word);

    std::vector<std::string> getSuggestions(const std::string& word);
};

#endif // TRIE_H
