#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void computePrefixFunction(const std::string& pattern, std::vector<int>& prefix) {
    int m = pattern.length();
    prefix.resize(m);
    prefix[0] = 0;

    int k = 0;
    for (int q = 1; q < m; q++) {
        while (k > 0 && pattern[k] != pattern[q]) {
            k = prefix[k - 1];
        }
        if (pattern[k] == pattern[q]) {
            k++;
        }
        prefix[q] = k;
    }
}

void KMPAlgorithm(const std::string& pattern, const std::string& text, int patternIndex) {
    int m = pattern.length();
    int n = text.length();
    std::vector<int> prefix;
    computePrefixFunction(pattern, prefix);

    int q = 0;
    for (int i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i]) {
            q = prefix[q - 1];
        }
        if (pattern[q] == text[i]) {
            q++;
        }
        if (q == m) {
            std::cout << i - m + 2 - pattern.length() << ", " << patternIndex + 1 << std::endl;
            q = prefix[q - 1];
        }
    }
}

int main() {
    std::string pattern;
    std::getline(std::cin, pattern);

    std::string line;
    std::vector<std::string> textLines;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            for (int patternIndex = 0; patternIndex < textLines.size(); patternIndex++) {
                std::istringstream iss(textLines[patternIndex]);
                std::string word;
                while (iss >> std::skipws >> word) {
                    std::string cleanWord;
                    bool leadingZeros = true;
                    for (char c : word) {
                        if (c != '0') {
                            leadingZeros = false;
                        }
                        if (!leadingZeros) {
                            cleanWord += c;
                        }
                    }
                    KMPAlgorithm(pattern, cleanWord, patternIndex);
                }
            }
            textLines.clear();
        } else {
            textLines.push_back(line);
        }
    }

    return 0;
}
