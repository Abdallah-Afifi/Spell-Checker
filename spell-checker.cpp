#include "Trie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>  // Include the necessary header for isalpha

void printRed(const std::string& word) {
    // Print any misspelled words in red
    std::cout << "\033[31m" << word << "\033[0m";
}

int main() {
    // Create a trie
    trie trie;

    // Load the dictionary into memory line by line
    std::ifstream dictFile("dictionary.txt");
    if (!dictFile.is_open()) {
        std::cerr << "Error opening dictionary file." << std::endl;
        return 1;  // Return an error code
    }

    std::string word;
    while (getline(dictFile, word)) {
        trie.insertWord(word);
    }
    dictFile.close();

    // Take a sentence from user input
    std::string sentence;
    std::cout << "-------------------------------\n\nWELCOME TO THE SPELLING CHECKER\n\n-------------------------------\n\n";
    std::cout << "Enter your sentances here: ";
    getline(std::cin, sentence);

    // Remove punctuation and convert to lowercase
    sentence.erase(std::remove_if(sentence.begin(), sentence.end(), [](unsigned char c) {
        return !std::isalpha(c) && !std::isspace(c);
        }), sentence.end());

    for (char& c : sentence) {
        c = tolower(c);
    }

    // Separate the sentence into words
    std::stringstream ss(sentence);
    bool firstWord = true;
    std::vector<std::string> misspelledWords;
    
    std::cout << "\n";

    while (ss >> word) {
        if (!trie.searchWord(word)) {
            if (!firstWord) {
                std::cout << " ";
            }
            printRed(word);
            misspelledWords.push_back(word);
        }
        else {
            if (!firstWord) {
                std::cout << " ";
            }
            std::cout << word;
        }
        firstWord = false;
    }
    std::cout << std::endl;

    // Print suggestions for misspelled words
    for (const std::string& misspelledWord : misspelledWords) {
        std::vector<std::string> suggestions = trie.getSuggestions(misspelledWord);
        if (!suggestions.empty()) {
            std::cout << "\nSuggestions for " << misspelledWord << ": ";
            for (const std::string& suggestion : suggestions) {
                std::cout << suggestion << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}