#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10007;

struct Product
{
    string barcode;
    string name;
    string category;
    double price;
    int quantity;
};

struct Node
{
    Product data;
    Node *next;

    Node(Product p)
    {
        data = p;
        next = nullptr;
    }
};

class Inventory
{
private:
    Node *hashTable[TABLE_SIZE];

    int hashFunction(string barcode)
    {
        int hash = 0;

        for (int i = 0; i < barcode.length(); i++)
        {
            hash = (hash * 31 + barcode[i]) % TABLE_SIZE;
        }

        return hash;
    }

public:
    Inventory()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            hashTable[i] = nullptr;
        }
    }

    void addProduct(Product p)
    {
        int index = hashFunction(p.barcode);

        Node *temp = hashTable[index];

        while (temp != nullptr)
        {
            if (temp->data.barcode == p.barcode)
            {
                cout << "Product already exists!\n";
                return;
            }

            temp = temp->next;
        }

        Node *newNode = new Node(p);

        newNode->next = hashTable[index];
        hashTable[index] = newNode;

        cout << "Product added successfully.\n";
    }

    void searchProduct(string barcode)
    {
        int index = hashFunction(barcode);

        Node *temp = hashTable[index];

        while (temp != nullptr)
        {
            if (temp->data.barcode == barcode)
            {
                cout << "\nProduct Found!\n";
                cout << "Barcode: " << temp->data.barcode << endl;
                cout << "Name: " << temp->data.name << endl;
                cout << "Category: " << temp->data.category << endl;
                cout << "Price: " << temp->data.price << " EGP\n";
                cout << "Quantity: " << temp->data.quantity << endl;
                return;
            }

            temp = temp->next;
        }

        cout << "Product not found.\n";
    }

    void updatePrice(string barcode, double newPrice)
    {
        int index = hashFunction(barcode);

        Node *temp = hashTable[index];

        while (temp != nullptr)
        {
            if (temp->data.barcode == barcode)
            {
                temp->data.price = newPrice;
                cout << "Price updated successfully.\n";
                return;
            }

            temp = temp->next;
        }

        cout << "Product not found.\n";
    }

    void updateQuantity(string barcode, int newQuantity)
    {
        int index = hashFunction(barcode);

        Node *temp = hashTable[index];

        while (temp != nullptr)
        {
            if (temp->data.barcode == barcode)
            {
                temp->data.quantity = newQuantity;
                cout << "Quantity updated successfully.\n";
                return;
            }

            temp = temp->next;
        }

        cout << "Product not found.\n";
    }

    void deleteProduct(string barcode)
    {
        int index = hashFunction(barcode);

        Node *temp = hashTable[index];
        Node *prev = nullptr;

        while (temp != nullptr)
        {
            if (temp->data.barcode == barcode)
            {
                if (prev == nullptr)
                {
                    hashTable[index] = temp->next;
                }
                else
                {
                    prev->next = temp->next;
                }

                delete temp;

                cout << "Product deleted successfully.\n";
                return;
            }

            prev = temp;
            temp = temp->next;
        }

        cout << "Product not found.\n";
    }

    void displayAllProducts()
    {
        bool found = false;

        for (int i = 0; i < TABLE_SIZE; i++)
        {
            Node *temp = hashTable[i];

            while (temp != nullptr)
            {
                found = true;

                cout << "\n--------------------\n";
                cout << "Barcode: " << temp->data.barcode << endl;
                cout << "Name: " << temp->data.name << endl;
                cout << "Category: " << temp->data.category << endl;
                cout << "Price: " << temp->data.price << " EGP\n";
                cout << "Quantity: " << temp->data.quantity << endl;

                temp = temp->next;
            }
        }

        if (!found)
            cout << "Inventory is empty.\n";
    }

    void displayByCategory(string category)
    {
        bool found = false;

        for (int i = 0; i < TABLE_SIZE; i++)
        {
            Node *temp = hashTable[i];

            while (temp != nullptr)
            {
                if (temp->data.category == category)
                {
                    found = true;

                    cout << temp->data.name
                         << " | " << temp->data.barcode
                         << " | " << temp->data.price
                         << " EGP | Quantity: "
                         << temp->data.quantity << endl;
                }

                temp = temp->next;
            }
        }

        if (!found)
            cout << "No products found in this category.\n";
    }

    void clearInventory()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            Node *temp = hashTable[i];

            while (temp != nullptr)
            {
                Node *nextNode = temp->next;
                delete temp;
                temp = nextNode;
            }

            hashTable[i] = nullptr;
        }

        cout << "Inventory cleared.\n";
    }

    ~Inventory()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            Node *temp = hashTable[i];

            while (temp != nullptr)
            {
                Node *nextNode = temp->next;
                delete temp;
                temp = nextNode;
            }
        }
    }
};

int main()
{
    Inventory inventory;

    int choice;

    do
    {
        cout << "\n===== PRODUCT INVENTORY SYSTEM =====\n";
        cout << "1. Add Product\n";
        cout << "2. Search Product\n";
        cout << "3. Update Price\n";
        cout << "4. Update Quantity\n";
        cout << "5. Delete Product\n";
        cout << "6. Display All Products\n";
        cout << "7. Display Products By Category\n";
        cout << "8. Clear Inventory\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        string barcode, name, category;
        double price;
        int quantity;

        switch (choice)
        {
        case 1:
        {
            Product p;

            cout << "Enter barcode: ";
            cin >> p.barcode;

            cin.ignore();

            cout << "Enter product name: ";
            getline(cin, p.name);

            cout << "Enter category: ";
            getline(cin, p.category);

            cout << "Enter price: ";
            cin >> p.price;

            cout << "Enter quantity: ";
            cin >> p.quantity;

            inventory.addProduct(p);
            break;
        }

        case 2:
            cout << "Enter barcode: ";
            cin >> barcode;

            inventory.searchProduct(barcode);
            break;

        case 3:
            cout << "Enter barcode: ";
            cin >> barcode;

            cout << "Enter new price: ";
            cin >> price;

            inventory.updatePrice(barcode, price);
            break;

        case 4:
            cout << "Enter barcode: ";
            cin >> barcode;

            cout << "Enter new quantity: ";
            cin >> quantity;

            inventory.updateQuantity(barcode, quantity);
            break;

        case 5:
            cout << "Enter barcode: ";
            cin >> barcode;

            inventory.deleteProduct(barcode);
            break;

        case 6:
            inventory.displayAllProducts();
            break;

        case 7:
            cin.ignore();

            cout << "Enter category: ";
            getline(cin, category);

            inventory.displayByCategory(category);
            break;

        case 8:
            inventory.clearInventory();
            break;

        case 0:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
