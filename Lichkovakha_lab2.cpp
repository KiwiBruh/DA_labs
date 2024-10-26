#include <iostream>
#include <fstream>
#include <string>
#include <map>

class Dictionary {
private:
    std::map<std::string, uint64_t> dict;

public:
    std::string addWord(const std::string& word, uint64_t number) {
        auto it = dict.find(word);
        if (it != dict.end()) {
            return "Exist";
        }

        dict[word] = number;
        return "OK";
    }

    std::string removeWord(const std::string& word) {
        auto it = dict.find(word);
        if (it == dict.end()) {
            return "NoSuchWord";
        }

        dict.erase(it);
        return "OK";
    }

    std::string findWord(const std::string& word) {
        auto it = dict.find(word);
        if (it == dict.end()) {
            return "NoSuchWord";
        }

        return "OK: " + std::to_string(it->second);
    }

    std::string saveDictionary(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            return "ERROR: Could not open file for writing";
        }

        for (const auto& entry : dict) {
            file.write(entry.first.c_str(), entry.first.length() + 1);
            file.write(reinterpret_cast<const char*>(&entry.second), sizeof(uint64_t));
        }

        return "OK";
    }

    std::string loadDictionary(const std::string& filename) {
        std::map<std::string, uint64_t> newDict;

        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            return "ERROR: Could not open file for reading";
        }

        std::string word;
        uint64_t number;

        while (file.read(reinterpret_cast<char*>(&word[0]), word.capacity()) && file.read(reinterpret_cast<char*>(&number), sizeof(uint64_t))) {
            newDict[word] = number;
        }

        dict = newDict;
        return "OK";
    }
};

int main() {
    std::string line;
    Dictionary dictionary;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }

        std::string command = line.substr(0, 1);
        std::string argument = line.substr(2);

        if (command == "+") {
            std::string word;
            uint64_t number;
            size_t space_pos = argument.find(' ');
            word = argument.substr(0, space_pos);
            number = std::stoull(argument.substr(space_pos + 1));
            std::cout << dictionary.addWord(word, number) << std::endl;
        } else if (command == "-") {
            std::cout << dictionary.removeWord(argument) << std::endl;
        } else if (command == "!") {
            std::string action = argument.substr(0, 4);
            std::string filename = argument.substr(5);

            if (action == "Save") {
                std::cout << dictionary.saveDictionary(filename) << std::endl;
            } else if (action == "Load") {
                std::cout << dictionary.loadDictionary(filename) << std::endl;
            }
        } else {
            std::cout << dictionary.findWord(line) << std::endl;
        }
    }

    return 0;
}