#include "GroceryTracker.h" 
#include <iostream> 
#include <iomanip> 
#include <algorithm> 
#include <vector> 
#include <utility>
#include <limits> 
#include <cctype>


// Stores the frequency map received from FileManager 

void GroceryTracker::loadData(const std::map<std::string, int>& data) {

    itemFreq = data;

}



// Builds a sorted vector of item/count pairs based on the chosen SortMode 

std::vector<std::pair<std::string, int>>

GroceryTracker::getSorted(SortMode mode) const {

    std::vector<std::pair<std::string, int>>

        items(itemFreq.begin(), itemFreq.end());



    if (mode == SortMode::FREQ_DESC) {

        std::sort(items.begin(), items.end(),

            [](const std::pair<std::string, int>& a,

                const std::pair<std::string, int>& b) {

                    return (a.second != b.second) ? a.second > b.second

                        : a.first < b.first;

            });

    }
    else if (mode == SortMode::FREQ_ASC) {

        std::sort(items.begin(), items.end(),

            [](const std::pair<std::string, int>& a,

                const std::pair<std::string, int>& b) {

                    return (a.second != b.second) ? a.second < b.second

                        : a.first < b.first;

            });

    }

    return items;

}



// Returns the purchase count for a specific item; 0 if absent 

int GroceryTracker::getFrequency(const std::string& item) const {

    std::string normalized = item;

    std::transform(normalized.begin(), normalized.end(),

        normalized.begin(), ::tolower);

    if (!normalized.empty()) {

        normalized[0] = static_cast<char>(toupper(normalized[0]));

    }

    auto it = itemFreq.find(normalized);

    return (it != itemFreq.end()) ? it->second : 0;

}



// Prints every item and its count in aligned columns 

void GroceryTracker::printAll(SortMode mode) const {

    auto items = getSorted(mode);

    std::cout << "\n" << std::string(36, '-') << "\n";

    std::cout << std::left << std::setw(22) << "Item"

        << std::setw(10) << "Count" << "\n";

    std::cout << std::string(36, '-') << "\n";

    for (const auto& pair : items) {

        std::cout << std::left << std::setw(22) << pair.first

            << std::setw(10) << pair.second << "\n";

    }

    std::cout << std::string(36, '-') << "\n";

}



// Prints a text histogram - one asterisk per purchase 

void GroceryTracker::printHistogram(SortMode mode) const {

    auto items = getSorted(mode);

    std::cout << "\n" << std::string(50, '-') << "\n";

    for (const auto& pair : items) {

        std::cout << std::left << std::setw(20) << pair.first;

        std::cout << std::string(pair.second, '*') << "\n";

    }

    std::cout << std::string(50, '-') << "\n";

}



// Prints summary statistics across all items 

void GroceryTracker::printSummary() const {

    if (itemFreq.empty()) {

        std::cout << "No data available.\n";

        return;

    }

    int total = 0;

    int maxCount = std::numeric_limits<int>::min();

    int minCount = std::numeric_limits<int>::max();

    std::string mostBought, leastBought;



    for (const auto& pair : itemFreq) {

        total += pair.second;

        if (pair.second > maxCount) {

            maxCount = pair.second;

            mostBought = pair.first;

        }

        if (pair.second < minCount) {

            minCount = pair.second;

            leastBought = pair.first;

        }

    }



    std::cout << "\n" << std::string(40, '=') << "\n";

    std::cout << "  SUMMARY STATISTICS\n";

    std::cout << std::string(40, '=') << "\n";

    std::cout << std::left << std::setw(26)

        << "  Unique items tracked:" << itemFreq.size() << "\n";

    std::cout << std::left << std::setw(26)

        << "  Total transactions:" << total << "\n";

    std::cout << std::left << std::setw(26)

        << "  Most purchased:"

        << mostBought << " (" << maxCount << ")\n";

    std::cout << std::left << std::setw(26)

        << "  Least purchased:"

        << leastBought << " (" << minCount << ")\n";

    std::cout << std::string(40, '=') << "\n";

}



// Returns true when no data has been loaded 

bool GroceryTracker::isEmpty() const {

    return itemFreq.empty();

}