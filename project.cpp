#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// ClothingItem class to represent a piece of clothing
class ClothingItem {
private:
    int id;
    string type;
    string brand;
    string color;
    string size;
    string style;
    string image;

public:
    ClothingItem() {
        id = 0;
        type = "";
        brand = "";
        color = "";
        size = "";
        style = "";
        image = "";
    }

    ClothingItem(int id, string type, string brand, string color, string size, string style, string image) {
        this->id = id;
        this->type = type;
        this->brand = brand;
        this->color = color;
        this->size = size;
        this->style = style;
        this->image = image;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    string getType() const {
        return type;
    }

    void setType(string type) {
        this->type = type;
    }

    string getBrand() const {
        return brand;
    }

    void setBrand(string brand) {
        this->brand = brand;
    }

    string getColor() const {
        return color;
    }

    void setColor(string color) {
        this->color = color;
    }

    string getSize() const {
        return size;
    }

    void setSize(string size) {
        this->size = size;
    }

    string getStyle() const {
        return style;
    }

    void setStyle(string style) {
        this->style = style;
    }

    string getImage() const {
        return image;
    }

    void setImage(string image) {
        this->image = image;
    }

    void printClothingItem() const {
        cout << "Clothing ID: " << id << endl;
        cout << "Type: " << type << endl;
        cout << "Brand: " << brand << endl;
        cout << "Color: " << color << endl;
        cout << "Size: " << size << endl;
        cout << "Style: " << style << endl;
        cout << "Image: " << image << endl;
    }
};

// Outfit class to represent a collection of clothing items
class Outfit {
private:
    int id;
    string name;
    vector<ClothingItem> clothingItems;
    string image;

public:
    Outfit() {
        id = 0;
        name = "";
        image = "";
    }

    Outfit(int id, string name, vector<ClothingItem> clothingItems, string image) {
        this->id = id;
        this->name = name;
        this->clothingItems = clothingItems;
        this->image = image;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    string getName() const {
        return name;
    }

    void setName(string name) {
        this->name = name;
    }

    vector<ClothingItem> getClothingItems() const {
        return clothingItems;
    }

    void setClothingItems(vector<ClothingItem> clothingItems) {
        this->clothingItems = clothingItems;
    }

    string getImage() const {
        return image;
    }

    void setImage(string image) {
        this->image = image;
    }

    void addClothingItem(ClothingItem clothingItem) {
        clothingItems.push_back(clothingItem);
}
void removeClothingItem(int index) {
    clothingItems.erase(clothingItems.begin() + index);
}

void printOutfit() const {
    cout << "Outfit ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Image: " << image << endl;
    cout << "Clothing Items: " << endl;
    for (const ClothingItem& item : clothingItems) {
        item.printClothingItem();
        cout << endl;
    }
}
};

// function to read clothing items from a file
vector<ClothingItem> readClothingItemsFromFile(string filename) {
vector<ClothingItem> clothingItems;
ifstream infile(filename);
if (infile.is_open()) {
int id;
string type;
string brand;
string color;
string size;
string style;
string image;
    while (infile >> id >> type >> brand >> color >> size >> style >> image) {
        ClothingItem clothingItem(id, type, brand, color, size, style, image);
        clothingItems.push_back(clothingItem);
    }
}
infile.close();
return clothingItems;
}

// function to write clothing items to a file
void writeClothingItemsToFile(vector<ClothingItem> clothingItems, string filename) {
ofstream outfile(filename);
if (outfile.is_open()) {
for (const ClothingItem& item : clothingItems) {
outfile << item.getId() << " " << item.getType() << " " << item.getBrand() << " " << item.getColor()
<< " " << item.getSize() << " " << item.getStyle() << " " << item.getImage() << endl;
}
}
outfile.close();
}


int main() 
{
// read clothing items from a file
vector<ClothingItem> clothingItems = readClothingItemsFromFile("clothing_items.txt");
// create an outfit and add some clothing items to it
Outfit outfit(1, "Casual Friday", {}, "");
outfit.addClothingItem(clothingItems[0]);
outfit.addClothingItem(clothingItems[2]);
outfit.addClothingItem(clothingItems[4]);

// print the outfit
outfit.printOutfit();

// write clothing items to a file
writeClothingItemsToFile(clothingItems, "output.txt");

return 0;
}
