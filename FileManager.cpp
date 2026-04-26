#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

// Bug 1: method was misspelled "sanatizeLine" — fixed to "sanitizeLine"
std::string FileManager::sanitizeLine(const std::string& line) const {
    // Bug 2: "find first not of" had spaces — must be find_first_not_of
    size_t start = line.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    // Bug 3: same — find_last_not_of
    size_t end = line.find_last_not_of(" \t\r\n");
    std::string trimmed = line.substr(start, end - start + 1);
    // Bug 4: std::transform was written as a constructor, not a function call
    std::transform(trimmed.begin(), trimmed.end(),
        trimmed.begin(), ::tolower);
    if (!trimmed.empty()) {
        // Bug 5: trimmed{ 0 } is not valid — must be trimmed[0]
        trimmed[0] = static_cast<char>(toupper(trimmed[0]));
    }
    return trimmed;
}

std::map<std::string, int>
FileManager::loadFile(const std::string& filename) const {
    std::map<std::string, int> freqMap; // Bug 6: freqMap was used but never declared
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        // Bug 7: >> used instead of << in the cerr line
        std::cerr << "Error: Could not open '" << filename << "'.\n";
        return freqMap;
    }
    std::string word;
    while (inFile >> word) {
        std::string clean = sanitizeLine(word);
        if (!clean.empty()) {
            freqMap[clean]++;
        }
    }
    inFile.close();
    return freqMap;
}

// Bug 8: saveToFile was missing its ofstream, opening brace, and the
// for loop was written outside the function entirely
void FileManager::saveToFile(const std::string& filename,
    const std::map<std::string, int>& data) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not write to '" << filename << "'.\n";
        return;
    }
    for (const auto& pair : data) {
        outFile << pair.first << " " << pair.second << "\n";
    }
    outFile.close();
}

bool FileManager::validateFile(const std::string& filename) const {
    std::ifstream f(filename);
    return f.good();
}