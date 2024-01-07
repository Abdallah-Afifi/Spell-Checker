#include "Trie.h"

#include <iostream>

const int ALPHABET_SIZE = 26;

TrieNode::TrieNode() : endOfWord(false), children(ALPHABET_SIZE, nullptr) {}

TrieNode::~TrieNode() {
    // Implement destructor logic to free allocated memory
    for (TrieNode* child : children) {
        delete child;
    }
    children.clear();
}

trie::trie() : root(new TrieNode()) {}

trie::~trie() {
    // Implement destructor logic to free allocated memory
    delete root;
    root = nullptr;
}

void trie::insertWord(const std::string& word) {
    TrieNode* currentNode = root;
    for (char c : word) {
        int index = tolower(c) - 'a';
        if (currentNode->children[index] == nullptr) {
            currentNode->children[index] = new TrieNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->endOfWord = true;
}

bool trie::searchWord(const std::string& word) {
    TrieNode* currentNode = root;
    for (char c : word) {
        int index = c - 'a';
        if (currentNode->children[index] == nullptr) {
            return false;
        }
        currentNode = currentNode->children[index];
    }
    return currentNode != nullptr && currentNode->endOfWord;
}

std::vector<std::string> trie::getSuggestions(const std::string& word) {
    std::vector<std::string> suggestions;

    // Generate suggestions by changing each character
    for (int i = 0; i < word.length(); ++i) {
        for (char c = 'a'; c <= 'z'; c++) {
            std::string modified = word;
            modified[i] = c;
            if (!modified.empty() && searchWord(modified)) {
                suggestions.push_back(modified);
            }
        }
    }

    // Generate suggestions by inserting each character
    for (int i = 0; i <= word.length(); ++i) {
        for (char c = 'a'; c <= 'z'; c++) {
            std::string modified = word;
            modified.insert(i, 1, c);
            if (!modified.empty() && searchWord(modified)) {
                suggestions.push_back(modified);
            }
        }
    }

    // Generate suggestions by deleting each character
    for (int i = 0; i < word.length(); ++i) {
        std::string modified = word;
        modified.erase(i, 1);
        if (!modified.empty() && searchWord(modified)) {
            suggestions.push_back(modified);
        }
    }

    // Generate suggestions by swapping adjacent characters
    for (int i = 0; i < word.length() - 1; ++i) {
        std::string modified = word;
        std::swap(modified[i], modified[i + 1]);
        if (!modified.empty() && searchWord(modified)) {
            suggestions.push_back(modified);
        }
    }

    return suggestions;
}
