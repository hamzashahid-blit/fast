#include <iostream>
#include <vector>
#include <map>
#include <memory>

class Book {
public:
    std::string title;
    std::string isbn;

    Book(std::string t, std::string i) : title(t), isbn(i) {}
};

class Catalog {
private:
    std::map<std::string, std::string> isbnToLocation;

public:
    void addBook(const std::string& isbn, const std::string& location) {
        isbnToLocation[isbn] = location;
    }

    std::string findBook(const std::string& isbn) {
        if (isbnToLocation.find(isbn) != isbnToLocation.end()) {
            return isbnToLocation[isbn];
        }
        return "Book not found.";
    }
};

class Library {
private:
    Catalog catalog;
    std::vector<std::shared_ptr<Book>> books;

public:
    void addBook(std::shared_ptr<Book> book, const std::string& location) {
        books.push_back(book);
        catalog.addBook(book->isbn, location);
    }

    std::string findBookInCatalog(const std::string& isbn) {
        return catalog.findBook(isbn);
    }
};

int main() {
    Library library;
    auto book1 = std::make_shared<Book>("1984", "12345");
    auto book2 = std::make_shared<Book>("Brave New World", "67890");

    library.addBook(book1, "A1");
    library.addBook(book2, "B2");

    std::cout << "Search for ISBN 12345: " << library.findBookInCatalog("12345") << std::endl;
    std::cout << "Search for ISBN 67890: " << library.findBookInCatalog("67890") << std::endl;

    return 0;
}
