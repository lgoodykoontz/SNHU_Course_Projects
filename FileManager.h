#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <map>

class FileManager {
private:
    std::string sanitizeLine(const std::string& line) const;

public:
    std::map<std::string, int> loadFile(const std::string& filename) const;

    void saveToFile(const std::string& filename,
        const std::map<std::string, int>& data) const;

    bool validateFile(const std::string& filename) const;
};

#endif