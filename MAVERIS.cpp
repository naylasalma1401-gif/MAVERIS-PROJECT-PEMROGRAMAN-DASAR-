#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


class Item {
    private:
        string code;
        string name;
        int stock;
        double price;

    public:
        Item() {}

        Item( string c, string n, int s, double p) {
            code  = c;
            name  = n;
            stock = s;
            price = p;
        }
        string getCode() { return code; }
        string getName() { return name; }
        int getStock() { return stock; }
        double getPrice() { return price; }

        void setName(string n) { name = n; }
        void setStock (int s) { stock = s; }
        void setPrice(double p) { price = p;}

        void display() {
            cout << code << " | " << name << " | stock: " << stock << " | Price : " << price << endl;
            }
        };

        class Inventory {
            private:
                vector<Item> items;
            
            public:

                void loadFromFile() {
                    ifstream file ("input.txt");
                    if (!file.is_open()) {
                        cout << " file input tidak ditemukan";
                        return;
                    }

                    string line;
                    while (getline(file, line)) {
                        stringstream ss(line);
                        string code, name, stockStr, priceStr;

                        getline(ss, code, ';');
                        getline(ss, name, ';');
                        getline(ss, stockStr, ';');
                        getline(ss, priceStr,  ';');

                        int stock = stoi(stockStr);
                        double price = stod(priceStr) ;

                        items.push_back(Item(code, name, stock, price));
                    
                    }

                    file.close();
                    cout << "data berhasil dimuat dari file input";
                }

                void saveToFile() {
                        ofstream file("output.txt");

                        for(Item&item : items) {
                            file << item.getCode() << ";" <<item.getName() << ";" << item.getPrice() << endl;
                        }
                        file.close();
                        cout << "data berhasil disimpan"; }
                
                void addItem() {
                        string code, name;
                        int stock;
                        double price;

                        cout << "Input Item's Code : "; cin >> code;
                        cout << "Input Item's Name : "; cin.ignore();
                        getline(cin, name);
                        cout << "Input Stock       : "; cin >> stock;
                        cout << "Input Price       : "; cin >> price;

                        items.push_back(Item(code, name, stock, price));
                        cout << "Item Added Successfully";
                    }

                    int findIndex(string code) {
                        for (int i = 0; i < items.size() ;i++) {
                            if (items[i].getCode() == code)
                                return i;
                        }
                        return -1;
                    }

                    void editItem() {
                        string code;
                        cout << "Input Item's Code : "; cin >> code;

                        int idx = findIndex(code);

                        if (idx == -1) {
                            cout << " item's not detected";
                            return;
                        }

                        string newName;
                        int newStock;
                        double newPrice;

                        cout << "New Name : ";
                        cin.ignore();
                        getline(cin, newName) ;
                        cout << "New Stock : ";
                        cin >> newStock;
                        cout << "New Price : ";
                        cin >> newPrice;

                        items[idx].setName(newName);
                        items[idx].setStock(newStock);
                        items[idx].setPrice(newPrice);

                        cout << "item's successly updated!" ;
                    }

                    void deleteItem() {
                        string code;
                        cout << "input item's code : ";
                        cin >> code;

                        int idx = findIndex(code) ;

                        if (idx == -1) {
                            cout << "item's not detected";
                            return;
                        }

                        items.erase(items.begin() + idx);
                        cout << "Item Succeslly deleted" ;
                    }

                    void showItems() {
                        cout << "-------List Item-------\n";
                        if (items.empty()) {
                            cout << "Tidak ada data barang. \n";
                            return;
                        }
                        for (Item &item : items) {
                            item.display();
                        }
                    }

                    void searchItem() {
                        string code;
                        cout << "input item's code: ";
                        cin >> code;

                        int idx  = findIndex(code);

                        if (idx == -1) {
                            cout << "item's not detected!\n" ;
                            return ;
                        }

                        cout << "FOUND ";
                        items[idx].display();
                    }
                };

                int main() {
                    Inventory inv;
                    inv.loadFromFile();

                    int choice;

                    do{
                        cout << "\n-----INVENTARIS-----\n";
                        cout << "1. Add Item\n";
                        cout << "2. Edit Item\n";
                        cout << "3. Delete Item\n";
                        cout << "4. Show All Items\n";
                        cout << "5. Find Item\n";
                        cout << "6. Save Data to File\n";
                        cout << "0. Exit\n";
                        cout << "Select Menu: ";
                        cin >> choice;

                        switch (choice) {
                            case 1: inv.addItem(); break;
                            case 2: inv.editItem(); break;
                            case 3: inv.deleteItem(); break;
                            case 4: inv.showItems(); break;
                            case 5: inv.searchItem(); break;
                            case 6: inv.saveToFile(); break;
                            case 0: cout << "Keluar program...\n"; break;
                            default: cout << "Pilihan salah!\n";
                        }

                    } while (choice != 0);

                    return 0;
                }
    