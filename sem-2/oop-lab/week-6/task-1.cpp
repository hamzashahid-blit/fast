#include <iostream>
#include <string>

// Base class for Books
class Books {
private:
    std::string genre; // Genre of the book

public:
    // Constructor to initialize genre
    Books(const std::string& bookGenre) : genre(bookGenre) {}

    // Getter for genre
    std::string getGenre() const {
        return genre;
    }

    // Virtual function to display book details (to be overridden by derived classes)
    virtual void displayDetails() const = 0; // Pure virtual function to make Books an abstract class
};

// Derived class for Novels
class Novel : public Books {
private:
    std::string title;  // Title of the novel
    std::string author; // Author of the novel

public:
    // Constructor to initialize Novel details
    Novel(const std::string& novelTitle, const std::string& novelAuthor)
        : Books("Novel"), title(novelTitle), author(novelAuthor) {}

    // Override displayDetails to show Novel-specific details
    void displayDetails() const override {
        std::cout << "Genre: " << getGenre() << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
};

// Derived class for Mystery books
class Mystery : public Books {
private:
    std::string title;  // Title of the mystery book
    std::string author; // Author of the mystery book

public:
    // Constructor to initialize Mystery details
    Mystery(const std::string& mysteryTitle, const std::string& mysteryAuthor)
        : Books("Mystery"), title(mysteryTitle), author(mysteryAuthor) {}

    // Override displayDetails to show Mystery-specific details
    void displayDetails() const override {
        std::cout << "Genre: " << getGenre() << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
};

int main() {
    // Create objects of derived classes
    Novel novel1("To Kill a Mockingbird", "Harper Lee");
    Mystery mystery1("The Girl with the Dragon Tattoo", "Stieg Larsson");

    // Display details of the books
    std::cout << "Book Details:" << std::endl;
    novel1.displayDetails();
    mystery1.displayDetails();

    return 0;
}
