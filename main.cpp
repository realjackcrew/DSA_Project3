#include <iostream>

#include "Trie.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Trie booksTest;
    string filePath = "GoogleBookAPIDataset.txt";
    booksTest.parseBookCSV(filePath);

    string pre = "harry";
    cout << "harry prefix: " << booksTest.isPrefixExist(booksTest.root, pre) << endl;

    return 0;
}
