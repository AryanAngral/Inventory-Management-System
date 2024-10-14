#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Product {
private:
    int productID;
    string name;
    int stock;
    double price;

public:
    Product(int id, string n, int s, double p) : productID(id), name(n), stock(s), price(p) {}

    int getProductID() const { return productID; }
    string getName() const { return name; }
    int getStock() const { return stock; }
    double getPrice() const { return price; }

    void setStock(int s) { stock = s; }
    void setPrice(double p) { price = p; }

    void displayProduct() const {
        cout << "Product ID: " << productID << ", Name: " << name << ", Stock: " << stock << ", Price: $" << price << endl;
    }
};

class Supplier {
private:
    int supplierID;
    string name;
    string contact;

public:
    Supplier(int id, string n, string c) : supplierID(id), name(n), contact(c) {}

    int getSupplierID() const { return supplierID; }
    string getName() const { return name; }
    string getContact() const { return contact; }

    void displaySupplier() const {
        cout << "Supplier ID: " << supplierID << ", Name: " << name << ", Contact: " << contact << endl;
    }
};

class InventorySystem {
private:
    vector<Product> products;
    vector<Supplier> suppliers;
    string username;
    string password;

    // Mock users and roles for demonstration purposes
    const string adminUser = "admin";
    const string adminPass = "admin123";
    const string managerUser = "manager";
    const string managerPass = "manager123";

    bool authenticateUser(const string &user, const string &pass) {
        return (user == adminUser && pass == adminPass) || (user == managerUser && pass == managerPass);
    }

    bool isAdmin(const string &user) {
        return user == adminUser;
    }

public:
    bool login() {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        if (authenticateUser(username, password)) {
            cout << "Login successful!\n";
            return true;
        } else {
            cout << "Login failed. Invalid credentials.\n";
            return false;
        }
    }

    void addProduct() {
        if (!isAdmin(username)) {
            cout << "Only admin can add products.\n";
            return;
        }

        int id, stock;
        string name;
        double price;

        cout << "Enter Product ID: ";
        cin >> id;
        cout << "Enter Product Name: ";
        cin >> name;
        cout << "Enter Stock: ";
        cin >> stock;
        cout << "Enter Price: ";
        cin >> price;

        products.push_back(Product(id, name, stock, price));
        cout << "Product added successfully!\n";
    }

    void updateProduct() {
        int id, stock;
        double price;

        cout << "Enter Product ID to update: ";
        cin >> id;

        for (auto &product : products) {
            if (product.getProductID() == id) {
                cout << "Enter new Stock: ";
                cin >> stock;
                cout << "Enter new Price: ";
                cin >> price;

                product.setStock(stock);
                product.setPrice(price);
                cout << "Product updated successfully!\n";
                return;
            }
        }
        cout << "Product not found.\n";
    }

    void deleteProduct() {
        if (!isAdmin(username)) {
            cout << "Only admin can delete products.\n";
            return;
        }

        int id;
        cout << "Enter Product ID to delete: ";
        cin >> id;

        auto it = remove_if(products.begin(), products.end(), [id](const Product &p) {
            return p.getProductID() == id;
        });

        if (it != products.end()) {
            products.erase(it, products.end());
            cout << "Product deleted successfully!\n";
        } else {
            cout << "Product not found.\n";
        }
    }

    void displayAllProducts() const {
        if (products.empty()) {
            cout << "No products in inventory.\n";
            return;
        }
        for (const auto &product : products) {
            product.displayProduct();
        }
    }

    void addSupplier() {
        if (!isAdmin(username)) {
            cout << "Only admin can add suppliers.\n";
            return;
        }

        int id;
        string name, contact;

        cout << "Enter Supplier ID: ";
        cin >> id;
        cout << "Enter Supplier Name: ";
        cin >> name;
        cout << "Enter Contact: ";
        cin >> contact;

        suppliers.push_back(Supplier(id, name, contact));
        cout << "Supplier added successfully!\n";
    }

    void displayAllSuppliers() const {
        if (suppliers.empty()) {
            cout << "No suppliers in the system.\n";
            return;
        }
        for (const auto &supplier : suppliers) {
            supplier.displaySupplier();
        }
    }
};

// Main menu to run the Inventory Management System
void menu() {
    cout << "\n--- Inventory Management System ---\n";
    cout << "1. Add Product\n";
    cout << "2. Update Product\n";
    cout << "3. Delete Product\n";
    cout << "4. Display All Products\n";
    cout << "5. Add Supplier\n";
    cout << "6. Display All Suppliers\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    InventorySystem inventory;
    if (!inventory.login()) {
        return 0;
    }

    int choice;
    do {
        menu();
        cin >> choice;

        switch (choice) {
            case 1:
                inventory.addProduct();
                break;
            case 2:
                inventory.updateProduct();
                break;
            case 3:
                inventory.deleteProduct();
                break;
            case 4:
                inventory.displayAllProducts();
                break;
            case 5:
                inventory.addSupplier();
                break;
            case 6:
                inventory.displayAllSuppliers();
                break;
            case 7:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
