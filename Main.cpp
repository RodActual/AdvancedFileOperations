// Anthony Rodriguez
// CIS 1202-101
// 11/05/2023

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int NAME_SIZE = 40;

struct Product
{
    long number;
    char name[NAME_SIZE];
    double price;
    int quantity;
};

int showMenu();
void createFile(fstream&);
void displayFile(fstream&);
void displayRecord(fstream&, int);
void modifyRecord(fstream&);

int main()
{
    fstream file("inventory.dat", ios::binary | ios::in | ios::out);

    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    createFile(file);

    int choice;
    do
    {
        choice = showMenu();

        switch (choice)
        {
        case 1:
            displayFile(file);
            break;
        case 2:
        {
            int recordNumber;
            cout << "Enter the record number to display: ";
            cin >> recordNumber;
            displayRecord(file, recordNumber);
            break;
        }
        case 3:
            modifyRecord(file);
            break;
        case 4:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 4);

    file.close();

    return 0;
}

int showMenu()
{
    int choice;
  cout << "Menu:" << endl;
    cout << "1. Display the entire inventory" << endl;
    cout << "2. Display a particular product" << endl;
    cout << "3. Modify a product" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    return choice;

    cout << endl;
}

void createFile(fstream& file)
{
    Product p;
    p.number = 12345;
    strcpy_s(p.name, "Dog");
    p.price = 11.99;
    p.quantity = 5;
    file.write(reinterpret_cast<char*>(&p), sizeof(p));

    Product q;
    q.number = 54321;
    strcpy_s(q.name, "Cat");
    q.price = 12.99;
    q.quantity = 7;
    file.write(reinterpret_cast<char*>(&q), sizeof(q));

    Product r;
    r.number = 2126378;
    strcpy_s(r.name, "Owl");
    r.price = 13.99;
    r.quantity = 9;
    file.write(reinterpret_cast<char*>(&r), sizeof(r));
}

void displayFile(fstream& file)
{
    file.clear();
    file.seekg(0, ios::beg);

    Product p;
    int recordNumber = 1;

    while (file.read(reinterpret_cast<char*>(&p), sizeof(p)))
    {
        cout << "Record " << recordNumber << ": " << p.number << ", " << p.name << ", " << p.price << ", " << p.quantity << endl;
        recordNumber++;
    }

    if (file.eof()) {
        file.clear();
    }

    cout << endl;
}

void displayRecord(fstream& file, int recordNumber)
{
    file.clear();
    file.seekg((recordNumber - 1) * sizeof(Product), ios::beg);

    Product p;
    file.read(reinterpret_cast<char*>(&p), sizeof(p));

    cout << "Record " << recordNumber << ": " << p.number << ", " << p.name << ", " << p.price << ", " << p.quantity << endl << endl;
}

void modifyRecord(fstream& file)
{
    int recordNumber;
    cout << "Enter the record number to modify: ";
    cin >> recordNumber;

    file.clear();
    file.seekp((recordNumber - 1) * sizeof(Product), ios::beg);

    Product p;
   cout << "Enter new values for the product:" << endl;
    cout << "Number: ";
    cin >> p.number;
    cout << "Name: ";
    cin.ignore();
    cin.getline(p.name, NAME_SIZE);
    cout << "Price: ";
    cin >> p.price;
    cout << "Quantity: ";
    cin >> p.quantity;

    file.write(reinterpret_cast<char*>(&p), sizeof(p));

    cout << "Record " << recordNumber << " modified successfully." << endl << endl;
}
