#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void computeLPSArray(const std::string& pattern, std::vector<int>& lps) {
    int m = pattern.length();
    lps.resize(m);
    lps[0] = 0;

    int len = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void ADAlgorithm(const std::string& pattern, const std::string& text, std::ostream& output) {
    int m = pattern.length();
    int n = text.length();
    std::vector<int> lps;
    computeLPSArray(pattern, lps);

    int i = 0;
    int j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            output << i - j + 1 << std::endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    std::string pattern;
    std::getline(input, pattern);

    std::vector<std::string> patterns;
    std::string line;
    while (std::getline(input, line) && !line.empty()) {
        patterns.push_back(line);
    }

    std::string text;
    while (std::getline(input, line)) {
        text += line + " ";
    }

    int patternCount = patterns.size();
    if (patternCount == 1) {
        ADAlgorithm(patterns[0], text, output);
    } else {
        for (int i = 0; i < patternCount; i++) {
            ADAlgorithm(patterns[i], text, output);
        }
    }

    input.close();
    output.close();

    return 0;
}