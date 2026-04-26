#ifndef GROCERYTRACKER_H
#define GROCERYTRACKER_H

#include <string>
#include <map>
#include <vector>
#include <utility>

enum class SortMode {
    ALPHABETICAL,
    FREQ_DESC,
    FREQ_ASC
};

class GroceryTracker {
private:
    std::map<std::string, int> itemFreq;

    std::vector<std::pair<std::string, int>>
        getSorted(SortMode mode) const;

public:
    void loadData(const std::map<std::string, int>& data);
    int getFrequency(const std::string& item) const;
    void printAll(SortMode mode = SortMode::ALPHABETICAL) const;
    void printHistogram(SortMode mode = SortMode::ALPHABETICAL) const;
    void printSummary() const;
    bool isEmpty() const;
};

#endif