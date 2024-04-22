#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


HashTable::HashTable() {
    capacity = 100;
    size = 0;
    table.resize(capacity);
}

void HashTable::resize(int newCapacity) {

    capacity = newCapacity;
    std::vector<std::vector<std::pair<std::string,Book>>> newTable(capacity);

    for(int i = 0; i < table.size(); i++) {
        for(int j = 0; j < table[i].size(); j++) {
            newTable[hashFunction(table[i][j].first,capacity)].push_back(table[i][j]);
        }
    }

    table = newTable;
}

int HashTable::hashFunction(std::string& key, int size) {
    int hashValue = 0;
    for (char c : key) {
        hashValue = (31* hashValue + c) % size;
    }
    return hashValue;
}

void HashTable::insert(std::string& key, const Book& value) {
    if (size >= capacity) {
        resize(capacity*2);
    }
    table[hashFunction(key, capacity)].push_back({key, value});
    size++;
}

bool HashTable::contains(std::string& key) {

    bool output = false;

    for (auto& pair : table[hashFunction(key, capacity)]) {
        if (pair.first == key) {
            output = true;
        }
    }

    return output;
}

Book* HashTable::retrieve(std::string& key) {
    int index = hashFunction(key, capacity);
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            return &pair.second;
        }
    }
    return nullptr;
}


void HashTable::remove(std::string& key) {

    for (auto it = table[hashFunction(key, capacity)].begin(); it != table[hashFunction(key, capacity)].end(); it++)
        if (it->first == key) {
            size--;
            table[hashFunction(key, capacity)].erase(it);
            break;
        }

}


std::string HashTable::titleCleanup(std::string& title) {
    std::string output = title;

    for (char &i: output)
        i = std::tolower(i);

    int i = 0;
    while (i < output.size()) {
        if(std::islower(output.at(i))) {
            i++;
        } else {
            output.erase(i,1);
        }
    }

    return output;
}

void HashTable::parseCSVHash(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Book book;
        std::string temp;

        std::getline(ss, temp, '\t');
        std::getline(ss, temp, '\t');
        std::getline(ss, book.id, '\t');
        std::getline(ss, book.title, '\t');
        std::getline(ss, book.description, '\t');
        std::getline(ss, book.authors, '\t');
        std::getline(ss, book.categories, '\t');
        std::getline(ss, temp, '\t');
        book.avgRating = std::stof(temp);
        std::getline(ss, temp, '\t');
        book.isMature = (temp == "MATURE");
        std::getline(ss, book.publishDate, '\t');
        std::getline(ss, temp, '\r');
        book.pageCount = std::stoi(temp);

        book.print();

        std::string lowerCaseBookTitle = titleCleanup(book.title);
        insert(lowerCaseBookTitle, book);
    }
}