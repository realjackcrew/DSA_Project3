//
// Created by Kent Phipps on 4/17/24.
//
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>  // For std::tolower

#include "Trie.h"

std::string toLowerAndRemoveNonLetters(const std::string& input) {
    std::string output = input;

    // Transform all characters to lowercase
    std::transform(output.begin(), output.end(), output.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    // Remove characters that are not lowercase letters
    output.erase(std::remove_if(output.begin(), output.end(),
                                [](char c) { return !std::islower(c); }),
                 output.end());

    return output;
}

void Trie::insert(TrieNode *root, string &key, Book *book) {
    // Initialize the currentNode pointer
    TrieNode* currentNode = root;

    // Iterate across the length of the string
    for (auto letter : key) {

        // Check if the node exist for the current
        // character in the Trie.
        if (currentNode->children[letter - 'a'] == nullptr) {

            // If node for current character does not exist
            // then make a new node
            TrieNode* newNode = new TrieNode();

            // Keep the reference for the newly created
            // node.
            currentNode->children[letter - 'a'] = newNode;
        }

        // Now, move the current node pointer to the newly
        // created node.
        currentNode = currentNode->children[letter - 'a'];
    }

    // Increment the wordEndCount for the last currentNode
    // pointer this implies that there is a string ending at
    // currentNode.
    currentNode->wordCount++;
    currentNode->books.push_back(book);
}

void Trie::parseBookCSV(string& filePath) {
    ifstream file(filePath);
    string line;

    // Skip header line
    getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Book* book = new Book();
        std::string temp;

        std::getline(ss, temp, '\t');
        std::getline(ss, temp, '\t');
        std::getline(ss, book->id, '\t');
        std::getline(ss, book->title, '\t');
        std::getline(ss, book->description, '\t');
        std::getline(ss, book->authors, '\t');
        std::getline(ss, book->categories, '\t');
        std::getline(ss, temp, '\t');
        book->avgRating = stof(temp);
        std::getline(ss, temp, '\t');
        book->isMature = (temp == "MATURE");
        std::getline(ss, book->publishDate, '\t');
        std::getline(ss, temp, '\r');
        book->pageCount = stoi(temp);

        book->print();

        string lowerCase = toLowerAndRemoveNonLetters(book->title);
        cout << "TEST: " << lowerCase << endl;

        insert(root, lowerCase, book);
    }
}

bool Trie::isPrefixExist(TrieNode* root, string& key) {
    // Initialize the currentNode pointer
    TrieNode* currentNode = root;
    
    // Iterate across the length of the string
    for (auto letter : key) {

        // Check if the node exist for the current
        // character in the Trie.
        if (currentNode->children[letter - 'a'] == nullptr) {

            // Given word as a prefix does not exist in Trie
            return false;
        }

        // Move the currentNode pointer to the already
        // existing node for current character.
        currentNode = currentNode->children[letter - 'a'];
    }

    // Prefix exist in the Trie
    return true;
}

bool Trie::search_key(TrieNode* root, string& key){
    // Initialize the currentNode pointer
    // with the root node
    TrieNode* currentNode = root;

    // Iterate across the length of the string
    for (auto letter : key) {

        // Check if the node exist for the current
        // character in the Trie.
        if (currentNode->children[letter - 'a'] == nullptr) {

            // Given word does not exist in Trie
            return false;
        }

        // Move the currentNode pointer to the already 
        // existing node for current character.
        currentNode = currentNode->children[letter - 'a'];
    }

    return (currentNode->wordCount > 0);
}