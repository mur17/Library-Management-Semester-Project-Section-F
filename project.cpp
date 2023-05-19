#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class ClothingItem {
private:
    string name;
    string size;
    double price;

public:
    ClothingItem(const string& itemName, const string& itemSize, double itemPrice)
        : name(itemName), size(itemSize), price(itemPrice) {}

    string getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Size: " << size << endl;
        cout << "Price: $" << price << endl;
    }
};

class Closet {
private:
    vector<ClothingItem> items;

public:
    void addItem(const ClothingItem& item) {
        items.push_back(item);
    }

    void displayItems() const {
        for (const auto& item : items) {
            item.display();
            cout << "--------------------" << endl;
        }
    }

    void saveToFile(const string& filename) const {
        ofstream outFile(filename);

        if (outFile.is_open()) {
            for (const auto& item : items) {
                outFile << item.getName() << "," << item.getSize() << "," << item.getPrice() << endl;
            }

            outFile.close();
        } else {
            cerr << "Error: Unable to open file for writing." << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);

        if (inFile.is_open()) {
            items.clear();

            string line;
            while (getline(inFile, line)) {
                // Parse the line and create a new ClothingItem
                // Example line format: "Shirt,L,19.99"
                // Extract name, size, and price from the line and create a ClothingItem object
                // Add the ClothingItem object to the vector
            }

            inFile.close();
        } else {
            cerr << "Error: Unable to open file for reading." << endl;
        }
    }

    vector<ClothingItem> getRandomOutfit(int numItems) const {
        vector<ClothingItem> outfit;
        const int itemCount = items.size();

        if (numItems > itemCount) {
            cout << "Error: Insufficient items in the closet." << endl;
            return outfit;
        }

        srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator

        for (int i = 0; i < numItems; ++i) {
            int randomIndex = rand() % itemCount;
            outfit.push_back(items[randomIndex]);
        }

        return outfit;
    }
};

void displayMenu() {
    cout << "------------------------" << endl;
    cout << "1. Add item to closet" << endl;
    cout << "2. Display closet items" << endl;
    cout << "3. Save closet items to file" << endl;
    cout << "4. Load closet items from file" << endl;
    cout << "5. Generate random outfit" << endl;
    cout << "6. Exit" << endl;
    cout << "------------------------" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Closet myCloset;

    // Add some clothing items to the closet
    myCloset.addItem(ClothingItem("Shirt", "L", 19.99));
    myCloset.addItem(ClothingItem("Jeans", "M", 29.99));
    myCloset.addItem(ClothingItem("Sweater", "S", 39.99));
    // Add more clothing items here...

    int choice = 0;

    while (choice != 6) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Ignore any remaining newline character

        switch (choice) {
            case 1: {
                string name, size;
                double price;

                cout << "Enter item name: ";
                getline(cin, name);

                cout << "Enter item size: ";
                getline(cin, size);

                cout << "Enter item price: ";
                cin >> price;

                myCloset.addItem(ClothingItem(name, size, price));
                cout << "Item added to the closet." << endl;
                break;
            }
            case 2:
                myCloset.displayItems();
                break;
            case 3: {
                string filename;
                cout << "Enter filename to save: ";
                getline(cin, filename);

                myCloset.saveToFile(filename);
                cout << "Closet items saved to file." << endl;
                break;
            }
            case 4: {
                string filename;
                cout << "Enter filename to load: ";
                getline(cin, filename);

                myCloset.loadFromFile(filename);
                cout << "Closet items loaded from file." << endl;
                break;
            }
            case 5: {
                int numItems;
                cout << "Enter the number of items in the outfit: ";
                cin >> numItems;

                vector<ClothingItem> outfit = myCloset.getRandomOutfit(numItems);
                cout << "Random Outfit:" << endl;

                for (const auto& item : outfit) {
                    item.display();
                    cout << "--------------------" << endl;
                }

                break;
            }
            case 6:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
