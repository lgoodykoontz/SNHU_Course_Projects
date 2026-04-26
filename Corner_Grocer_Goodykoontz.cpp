#include "FileManager.h" 

#include "GroceryTracker.h" 

#include <iostream> 

#include <limits> 

#include <string> 



// Repeatedly prompts until the user enters an integer within [minVal, maxVal] 

int getValidatedInt(const std::string& prompt, int minVal, int maxVal) {

    int value;

    while (true) {

        std::cout << prompt;

        if (std::cin >> value && value >= minVal && value <= maxVal) {

            std::cin.ignore(

                std::numeric_limits<std::streamsize>::max(), '\n');

            return value;

        }

        std::cin.clear();

        std::cin.ignore(

            std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "  Invalid input. Please enter a number between "

            << minVal << " and " << maxVal << ".\n";

    }

}



// Asks the user to pick a sort order and returns the matching SortMode 

SortMode chooseSortMode() {

    std::cout << "\n  Sort by:\n";

    std::cout << "    1. Alphabetical (A-Z)\n";

    std::cout << "    2. Most purchased first\n";

    std::cout << "    3. Least purchased first\n";

    int choice = getValidatedInt("  Choice: ", 1, 3);

    if (choice == 2) return SortMode::FREQ_DESC;

    if (choice == 3) return SortMode::FREQ_ASC;

    return SortMode::ALPHABETICAL;

}



// Displays the main menu 

void displayMenu() {

    std::cout << "\n";

    std::cout << "  +----------------------------------+\n";

    std::cout << "  |     CORNER GROCER TRACKER        |\n";

    std::cout << "  +----------------------------------+\n";

    std::cout << "  |  1. Search for an item           |\n";

    std::cout << "  |  2. Display all frequencies      |\n";

    std::cout << "  |  3. Display histogram            |\n";

    std::cout << "  |  4. Show summary statistics      |\n";

    std::cout << "  |  5. Exit                         |\n";

    std::cout << "  +----------------------------------+\n";

}



int main() {

    const std::string INPUT_FILE = "CS210_Project_Three_Input_File.txt";

    const std::string BACKUP_FILE = "frequency.dat";



    FileManager fileManager;

    GroceryTracker tracker;



    // Validate file existence before attempting to read 

    if (!fileManager.validateFile(INPUT_FILE)) {

        std::cerr << "Error: '" << INPUT_FILE << "' not found.\n"

            << "Please place the input file in the project directory.\n";

        return 1;

    }



    // Load data through FileManager, then inject into GroceryTracker 

    auto freqData = fileManager.loadFile(INPUT_FILE);

    if (freqData.empty()) {

        std::cerr << "Error: Input file is empty or could not be read.\n";

        return 1;

    }



    tracker.loadData(freqData);



    // Write the backup file automatically at startup 

    fileManager.saveToFile(BACKUP_FILE, freqData);

    std::cout << "  Data loaded. Backup written to '"

        << BACKUP_FILE << "'.\n";



    int choice = 0;

    while (choice != 5) {

        displayMenu();

        choice = getValidatedInt("  Enter choice: ", 1, 5);



        switch (choice) {

        case 1: {

            std::cout << "  Enter item name: ";

            std::string item;

            std::getline(std::cin, item);

            if (item.empty()) {

                std::cout << "  No item entered.\n";

                break;

            }

            int freq = tracker.getFrequency(item);

            if (freq == 0) {

                std::cout << "  '" << item

                    << "' was not found in today's records.\n";

            }
            else {

                std::cout << "  " << item << " was purchased "

                    << freq << " time(s) today.\n";

            }

            break;

        }

        case 2:

            tracker.printAll(chooseSortMode());

            break;

        case 3:

            tracker.printHistogram(chooseSortMode());

            break;

        case 4:

            tracker.printSummary();

            break;

        case 5:

            std::cout << "\n  Goodbye!\n";

            break;

        }

    }

    return 0;

}