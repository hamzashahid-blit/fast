#include <iostream>
#include <sstream>
#include <array>

class Book {
    std::string name;
    long isbn;
    std::string author_name;
    std::string publisher;
public:
    Book(std::string_view name,
         long isbn,
         std::string_view author_name,
         std::string_view publisher)
        : name{name}, isbn{isbn}, author_name{author_name}, publisher{publisher} {};
    std::string get_book_info() {
        std::stringstream info {};
        info << '"' << this->name << "\" (" << this->isbn << "), by \""
             << this->author_name << "\". Published by " << this->publisher;
        return info.str();
    }
    
    std::string get_name() { return this->name; }
    long get_isbn() { return this->isbn; }
    std::string get_author_name() { return this->author_name; }
    std::string get_publisher() { return this->publisher; }
};

int main(int argc, char *argv[])
{
    std::array<Book, 5> books {
        Book("War and Peace",  9783161484100, "Leo Tolstoy", "Oxford"),
        Book("The Great Gatsby",  7374856355757, "F. Scott Fitzgerald", "Harvard"),
        Book("To Kill a Mockingbird",  2538565567579, "Harper Lee", "Urdu Bazaar"),
        Book("Animal Farm",  5647364758679, "George Orwell", "Sachels"),
        Book("The Fault in Our Stars",  1314050016476, "John Green", "Japan Times"),
    };

    for (Book book : books) {
        std::cout << book.get_book_info() << '\n';
    }
    
    return 0;
}
