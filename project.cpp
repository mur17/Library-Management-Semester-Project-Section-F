#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std;

const int MAX_CLOTHING_ITEMS = 1000;
const int MAX_OUTFITS = 100;

// Clothing class
class Clothing {
private:
    int id;
    string type;
    string brand;
    string color;
    string size;
    string style;
    string image;

public:
    // Constructor
    Clothing(int i, string t, string b, string c, string s, string st, string img) {
        id = i;
        type = t;
        brand = b;
        color = c;
        size = s;
        style = st;
        image = img;
    }

    // Getters
    int getId() const { return id; }
    string getType() const { return type; }
    string getBrand() const { return brand; }
    string getColor() const { return color; }
    string getSize() const { return size; }
    string getStyle() const { return style; }
    string getImage() const { return image; }
};

// Outfit class
class Outfit {
private:
    int id;
    string name;
    string image;
    vector<Clothing> items;

public:
    // Constructor
    Outfit(int i, string n, string img, vector<Clothing> it) {
        id = i;
        name = n;
        image = img;
        items = it;
    }

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    string getImage() const { return image; }
    vector<Clothing> getItems() const { return items; }
};

// Class to manage user's virtual wardrobe
// Class to manage user's virtual wardrobe
class Wardrobe {
private:
    // Vector of clothing items
    vector<Clothing> clothingItems;
    // Vector of outfits
    vector<Outfit> outfits;

    // Helper function to find the index of a clothing item in the vector
    int findClothingIndex(int clothingId) const {
        for (int i = 0; i < clothingItems.size(); i++) {
            if (clothingItems[i].getId() == clothingId) {
                return i;
            }
        }
        return -1;
    }

public:
    // Add a new clothing item to the wardrobe
    void addClothing(const Clothing& clothing) {
        if (clothingItems.size() < MAX_CLOTHING_ITEMS) {
            clothingItems.push_back(clothing);
            cout << "Clothing item added successfully!" << endl;
        } else {
            cout << "Maximum clothing items limit reached!" << endl;
        }
    }

    // Remove a clothing item from the wardrobe
    void removeClothing(int clothingId) {
        int index = findClothingIndex(clothingId);
        if (index != -1) {
            clothingItems.erase(clothingItems.begin() + index);
            cout << "Clothing item removed successfully!" << endl;
        } else {
            cout << "Clothing item not found!" << endl;
        }
    }

    // Update a clothing item in the wardrobe
    void updateClothing(int clothingId, const Clothing& clothing) {
        int index = findClothingIndex(clothingId);
        if (index != -1) {
            clothingItems[index] = clothing;
            cout << "Clothing item updated successfully!" << endl;
        } else {
            cout << "Clothing item not found!" << endl;
        }
    }

    // Add a new outfit to the wardrobe
    void addOutfit(const Outfit& outfit) {
        if (outfits.size() < MAX_OUTFITS) {
            outfits.push_back(outfit);
            cout << "Outfit added successfully!" << endl;
        } else {
            cout << "Maximum outfits limit reached!" << endl;
        }
    }
    
// Remove an outfit from the wardrobe
void removeOutfit(int outfitId) {
    for (int i = 0; i < outfits.size(); i++) {
        if (outfits[i].getId() == outfitId) {
            outfits.erase(outfits.begin() + i);
            cout << "Outfit removed successfully!" << endl;
            return;
        }
    }
    cout << "Outfit not found!" << endl;
}

// Get all clothing items in the wardrobe
vector<Clothing> getClothingItems() const {
    return clothingItems;
}

// Get all outfits in the wardrobe
vector<Outfit> getOutfits() const {
    return outfits;
}

// Save the wardrobe data to a file
void saveDataToFile(string fileName) const {
    ofstream outputFile;
    outputFile.open(fileName);

    // Save clothing items
    outputFile << "Clothing Items:" << endl;
    for (int i = 0; i < clothingItems.size(); i++) {
        outputFile << clothingItems[i].getId() << "," << clothingItems[i].getType() << ","
            << clothingItems[i].getBrand() << "," << clothingItems[i].getColor() << ","
            << clothingItems[i].getSize() << "," << clothingItems[i].getStyle() << ","
            << clothingItems[i].getImage() << endl;
    }

    // Save outfits
    outputFile << "Outfits:" << endl;
    for (int i = 0; i < outfits.size(); i++) {
        outputFile << outfits[i].getId() << "," << outfits[i].getName() << ","
            << outfits[i].getImage() << ",";
        for (int j = 0; j < outfits[i].getItems().size(); j++) {
            outputFile << outfits[i].getItems()[j].getId() << ";";
        }
        outputFile << endl;
    }

    outputFile.close();
    cout << "Data saved successfully to " << fileName << "!" << endl;
}
// Load the wardrobe from a file
void loadWardrobeFromFile(const string& fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        // Read clothing items from file
        int numClothingItems;
        file >> numClothingItems;
        for (int i = 0; i < numClothingItems; i++) {
            int id;
            string type, brand, color, size, style, image;
            file >> id >> type >> brand >> color >> size >> style >> image;
            Clothing clothing(id, type, brand, color, size, style, image);
            clothingItems.push_back(clothing);
        }

        // Read outfits from file
        int numOutfits;
        file >> numOutfits;
        for (int i = 0; i < numOutfits; i++) {
            int id;
            string name, image;
            file >> id >> name >> image;
            int numItems;
            file >> numItems;
            vector<Clothing> items;
            for (int j = 0; j < numItems; j++) {
                int itemId;
                file >> itemId;
                int index = findClothingIndex(itemId);
                if (index != -1) {
                    items.push_back(clothingItems[index]);
                }
            }
            Outfit outfit(id, name, image, items);
            outfits.push_back(outfit);
        }

        cout << "Wardrobe loaded from file successfully!" << endl;
    } else {
        cout << "Error: could not open file " << fileName << " for reading." << endl;
    }
}
};


// User class declaration
class User {
private:
    string username;
    string password;
    vector<Clothing*> clothingRecords;
    vector<Outfit*> outfitRecords;

public:
    // Constructor
    User(string name, string pass) {
        username = name;
        password = pass;
    }

    // Getter functions
    string getUsername() const {
        return username;
    }
    string getPassword() const {
        return password;
    }
    vector<Clothing*> getClothingRecords() const {
        return clothingRecords;
    }
    vector<Outfit*> getOutfitRecords() const {
        return outfitRecords;
    }

    // Setter functions
    void setUsername(string name) {
        username = name;
    }
    void setPassword(string pass) {
        password = pass;
    }
    void addClothingRecord(Clothing* record) {
        clothingRecords.push_back(record);
    }
    void removeClothingRecord(int index) {
        clothingRecords.erase(clothingRecords.begin() + index);
    }
};

int main()
{
    Wardrobe wardrobe;
    // Load data from file
    

// Menu loop
while (true) {
    cout << "===============================" << endl;
    cout << "Virtual Wardrobe" << endl;
    cout << "===============================" << endl;
    cout << "1. Add clothing item" << endl;
    cout << "2. Remove clothing item" << endl;
    cout << "3. View clothing items" << endl;
    cout << "4. Add outfit" << endl;
    cout << "5. Remove outfit" << endl;
    cout << "6. View outfits" << endl;
    cout << "7. Exit" << endl;

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int id;
            string type, brand, color, size, style, image;
            cout << "Enter clothing item ID: ";
            cin >> id;
            cout << "Enter clothing item type: ";
            cin >> type;
            cout << "Enter clothing item brand: ";
            cin >> brand;
            cout << "Enter clothing item color: ";
            cin >> color;
            cout << "Enter clothing item size: ";
            cin >> size;
            cout << "Enter clothing item style: ";
            cin >> style;
            cout << "Enter clothing item image path: ";
            cin >> image;
            Clothing clothing(id, type, brand, color, size, style, image);
            wardrobe.addClothing(clothing);
            break;
        }
        case 2: {
            int id;
            cout << "Enter clothing item ID: ";
            cin >> id;
            wardrobe.removeClothing(id);
            break;
        }
        case 3: {
            wardrobe.getClothingItems();
            break;
        }
        case 4: {
            int id;
            string name, image;
            vector<Clothing> items;
            cout << "Enter outfit ID: ";
            cin >> id;
            cout << "Enter outfit name: ";
            cin >> name;
            cout << "Enter outfit image path: ";
            cin >> image;
            cout << "Enter clothing items for the outfit (IDs separated by spaces): ";
            string itemIds;
            cin.ignore();
            getline(cin, itemIds);
            istringstream iss(itemIds);
            int itemId;
            while (iss >> itemId) {
                int index = wardrobe.findClothingIndex(itemId);
                if (index != -1) {
                    items.push_back(wardrobe.getClothingItems(index));
                } else {
                    cout << "Clothing item with ID " << itemId << " not found." << endl;
                }
            }
            Outfit outfit(id, name, image, items);
            wardrobe.addOutfit(outfit);
            break;
        }
        case 5: {
            int id;
            cout << "Enter outfit ID: ";
            cin >> id;
            wardrobe.removeOutfit(id);
            break;
        }
        case 6: {
            wardrobe.viewOutfits();
            break;
        }
        case 7: {
            // Exit program
            cout << "Goodbye!" << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

return 0;

}
