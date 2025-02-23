#include <iostream>
#include <string>

class Invoice {
private:
    std::string partNumber;
    std::string partDescription;
    int quantity;
    double pricePerItem;

public:
    Invoice(std::string number, std::string description, int qty, double price)
        : partNumber(number), partDescription(description), quantity(qty > 0 ? qty : 0), pricePerItem(price > 0 ? price : 0.0) {}

    double getInvoiceAmount() const {
        return quantity * pricePerItem;
    }
};

int main() {
    Invoice invoice("1234", "Hammer", 2, 15.99);
    std::cout << "Invoice Amount: " << invoice.getInvoiceAmount() << std::endl;
    return 0;
}
