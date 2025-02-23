#include <iostream>
#include <string>

class Books {
private:
    std::string author;
    std::string title;
    double price;
    std::string publisher;
    int stock;

public:
    Books(std::string auth, std::string ttl, double prc, std::string pub, int stk)
        : author(auth), title(ttl), price(prc), publisher(pub), stock(stk) {}

    void checkAvailability(int requestedCopies) {
        if (stock >= requestedCopies) {
            std::cout << "Book Available. Total Cost: " << (price * requestedCopies) << std::endl;
        } else {
            std::cout << "Required copies not in stock." << std::endl;
        }
    }
};

int main() {
    Books book("J.K. Rowling", "Harry Potter", 20.0, "Bloomsbury", 10);
    book.checkAvailability(5);
    return 0;
}
