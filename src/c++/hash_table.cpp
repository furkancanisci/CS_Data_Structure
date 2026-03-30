#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

class HashTable {
    public:
        HashTable(size_t size) : table(size) {}

        void insert(const std::string& key, int value) {
            size_t index = hash(key);
            table[index].push_back({key, value});
        }

        bool find(const std::string& key, int& value) {
            size_t index = hash(key);
            for (const auto& pair : table[index]) {
                if (pair.first == key) {
                    value = pair.second;
                    return true;
                }
            }
            return false;
        }

        bool remove(const std::string& key) {
            size_t index = hash(key);
            table[index].erase(std::remove_if(table[index].begin(), table[index].end(),
                [&key](const std::pair<std::string, int>& pair) {
                    return pair.first == key;
                }), table[index].end());

            return true;
        }

    private:
        std::vector<std::vector<std::pair<std::string, int>>> table;

        size_t hash(const std::string& key) {
            size_t hashValue = 0;
            for (char ch : key) {
                hashValue = hashValue * 31 + ch;
            }
            return hashValue % table.size();
        }
};

int main() {
    HashTable hashTable(10);
    hashTable.insert("apple", 1);
    hashTable.insert("banana", 2);
    hashTable.insert("orange", 3);

    
    hashTable.remove("apple");
    std::cout << "Removed 'apple'" << std::endl;
    
    int value;
    if (hashTable.find("banana", value)) {
        std::cout << "Value for 'banana': " << value << std::endl;
    } else {
        std::cout << "'banana' not found" << std::endl;
    }

    if (hashTable.find("grape", value)) {
        std::cout << "Value for 'grape': " << value << std::endl;
    } else {
        std::cout << "'grape' not found" << std::endl;
    }

    return 0;
}