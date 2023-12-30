#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Function prototypes declaration
void addParts(string key, vector<pair<string, int>>& inventory);
void removeParts(string key, vector<pair<string, int>>& inventory);
void addItem(vector<pair<string, int>>& inventory);
void displayInventory(const vector<pair<string, int>>& inventory);

/*
 * Adds parts to an item in the inventory based on the provided key.
 * 
 * @param key: The name/description of the item in inventory.
 * @param inventory: A reference to the vector holding inventory items.
 *
 */
void addParts(string key, vector<pair<string, int>>& inventory) {
    int add;

    cout << "Number of parts to add: ";
    
    // Get number of parts to add
    cin >> add;

    // Search for the item in the inventory by key
    for (auto& item : inventory) {
        if (item.first == key) {

            // Check if adding parts exceeds limit
            if(item.second + add > 30){
                cout << "Exceeding maximum number of parts";
                return;
            }

            // Add parts to the item
            item.second += add;
            
            // Exit loop once done
            break;
        }
    }

    // Show the updated inventory
    displayInventory(inventory);
}


/*
 * Removes parts from an item in the inventory based on the provided key.
 * 
 * @param key: The name/description of the item in inventory.
 * @param inventory: A reference to the vector holding inventory items.
 * 
 */
void removeParts(string key, vector<pair<string, int>>& inventory) {
    int removal;

    cout << "Number of parts to remove: ";

    // Get number of parts to remove
    cin >> removal;

    // Search for the item in the inventory by key
    for (auto& item : inventory) {
        if (item.first == key) {

            // Check if enough parts are available for removal
            if(item.second - removal < 0){
                cout << "Not enough parts to remove";
                return;
            }

            // Remove parts from the item
            item.second -= removal;
            
            // Exit loop once done
            break;
        }
    }

    // Show the updated inventory
    displayInventory(inventory);
}

/*
 * Adds a new item to the inventory.
 * 
 * @param inventory: A reference to the vector holding inventory items.
 */
void addItem(vector<pair<string, int>>& inventory) {
    string key;
    int value;

    cout << "Add Item" << endl;
    cout << "Enter Part Description: ";

    // Clear input buffer
    cin.ignore();

    // Get item description
    getline(cin, key);

    // Check if item already exists in the inventory
    for (const auto& item : inventory) {
        if (item.first == key) {

            // Exit if item exists
            cout << "Already in the bin" << endl;
            return;
        }
    }

    cout << "Number of Parts in the Bin: ";

    // Get number of parts for new item
    cin >> value;

    // Check if provided number of parts exceeds the limit
    if (value > 30) {
        cout << "Cannot add the item" << endl;
        return;
    }

    // Add new item to inventory
    inventory.push_back({key, value});

    // Show updated inventory
    displayInventory(inventory);
}

/*
 * Displays all items in the inventory.
 * 
 * @param inventory: A constant reference to the vector holding inventory items.
 * 
 */
void displayInventory(const vector<pair<string, int>>& inventory) {
    for (const auto& item : inventory) {
        // Display each item description and count in formatted manner
        cout << left << setw(20) << item.first << right << setw(3) << item.second << '\n';
    }
}

/* open input file, push back data into vector, display menu and
   run appropriate function called
*/
int main() {
    vector<pair<string, int>> inventory;

    // File stream for reading
    ifstream inFile;
    
    string line, fileName;
    bool open = false;

    // Loop until a valid inventory file is provided and opened
    while (!open) {
        cout << "Enter name of inventory file: ";
        cin >> fileName;
        inFile.open(fileName);
        if (inFile.is_open()) {
            // Mark as opened if successful
            open = true;
        } else {
            cout << "Error opening file. Please try again." << endl;
        }
    }

    string key;
    bool isKey = true;

    // Read the inventory from file
    // Assumes alternating lines of item description and count
    while (getline(inFile, line)) {
        if (isKey) {
            key = line;
        } else {
            inventory.push_back({key, stoi(line)});
        }
        
        isKey = !isKey;
    }

    // Close file after reading
    inFile.close();

    bool end = false;

    // Display initial inventory
    displayInventory(inventory);

    // Main loop for interactive menu
    do {
        char select, select2;

        cout << "\nMenu:" << endl;
        cout << "Add a new item (a)" << endl;
        cout << "Select a bin (s)" << endl;
        cout << "Quit (q)" << endl;
        cout << "\nSelection: ";
        cin >> select;

        switch (select) {
            case 'a':
                // Add new item option
                addItem(inventory);
                break;
            case 's': {
                string binSelect;
                cout << "Bin Selection: ";
                // Clear input buffer
                cin.ignore();
                // Get bin to select 
                getline(cin, binSelect);
                bool found = false;
                // Check if the selected bin exists in the inventory

                for (const auto& item : inventory) {
                    if (item.first == binSelect) {
                        // Mark as found if match
                        found = true;
                        break;
                    }
                }
                // Handle case where bin doesn't exist
                if (!found) {
                    cout << "No " << binSelect << " in bin" << endl;
                    break;
                }
                // Sub-menu for selected bin
                cout << "Menu:\n";
                cout << "Add parts (a)\n";
                cout << "Remove parts (r)\n";
                cout << "\nSelection: ";
                cin >> select2;
                // Add or remove parts based on sub-menu selection
                if (select2 == 'a') {
                    // call addParts function
                    addParts(binSelect, inventory);
                } else if (select2 == 'r') {
                    // call removeParts function
                    removeParts(binSelect, inventory);
                }
                break;
            }
            case 'q':
                cout << "Good Bye!!!" << endl;
                end = true;
                break;
            default:
                break;
        }
    // Continue until 'end' is marked true
    } while (!end);
    return 0;
}
