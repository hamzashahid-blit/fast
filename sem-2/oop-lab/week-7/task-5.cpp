#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Media {
protected:
    string title;
    string publicationDate;
    string uniqueID;
    string publisher;

public:
    Media(string t, string date, string id, string pub)
        : title(t), publicationDate(date), uniqueID(id), publisher(pub) {}

    // Getters
    string getTitle() const { return title; }
    string getPublicationDate() const { return publicationDate; }
    string getUniqueID() const { return uniqueID; }
    string getPublisher() const { return publisher; }

    virtual void displayInfo() {
        cout << "Title: " << title << "\n";
        cout << "Publication Date: " << publicationDate << "\n";
        cout << "ID: " << uniqueID << "\n";
        cout << "Publisher: " << publisher << "\n";
    }

    virtual void checkOut() {
        cout << title << " has been checked out.\n";
    }

    virtual void returnItem() {
        cout << title << " has been returned.\n";
    }
};

class Book : public Media {
private:
    string author;
    string ISBN;
    int numberOfPages;

public:
    Book(string t, string date, string id, string pub, string auth, string isbn, int pages)
        : Media(t, date, id, pub), author(auth), ISBN(isbn), numberOfPages(pages) {}

    // Getters
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
    int getNumberOfPages() const { return numberOfPages; }

    void displayInfo() override {
        Media::displayInfo();
        cout << "Type: Book\n";
        cout << "Author: " << author << "\n";
        cout << "ISBN: " << ISBN << "\n";
        cout << "Pages: " << numberOfPages << "\n";
    }
};

class DVD : public Media {
private:
    string director;
    int duration; // in minutes
    string rating;

public:
    DVD(string t, string date, string id, string pub, string dir, int dur, string rate)
        : Media(t, date, id, pub), director(dir), duration(dur), rating(rate) {}

    // Getters
    string getDirector() const { return director; }
    int getDuration() const { return duration; }
    string getRating() const { return rating; }

    void displayInfo() override {
        Media::displayInfo();
        cout << "Type: DVD\n";
        cout << "Director: " << director << "\n";
        cout << "Duration: " << duration << " minutes\n";
        cout << "Rating: " << rating << "\n";
    }
};

class CD : public Media {
private:
    string artist;
    int numberOfTracks;
    string genre;

public:
    CD(string t, string date, string id, string pub, string art, int tracks, string gen)
        : Media(t, date, id, pub), artist(art), numberOfTracks(tracks), genre(gen) {}

    // Getters
    string getArtist() const { return artist; }
    int getNumberOfTracks() const { return numberOfTracks; }
    string getGenre() const { return genre; }

    void displayInfo() override {
        Media::displayInfo();
        cout << "Type: CD\n";
        cout << "Artist: " << artist << "\n";
        cout << "Tracks: " << numberOfTracks << "\n";
        cout << "Genre: " << genre << "\n";
    }
};

class Magazine : public Media {
private:
    int issueNumber;
    string ISSN;

public:
    Magazine(string t, string date, string id, string pub, int issue, string issn)
        : Media(t, date, id, pub), issueNumber(issue), ISSN(issn) {}

    // Getters
    int getIssueNumber() const { return issueNumber; }
    string getISSN() const { return ISSN; }

    void displayInfo() override {
        Media::displayInfo();
        cout << "Type: Magazine\n";
        cout << "Issue: " << issueNumber << "\n";
        cout << "ISSN: " << ISSN << "\n";
    }
};

class Library {
private:
    vector<Media*> collection;

public:
    // Getter for collection (const version)
    const vector<Media*>& getCollection() const { return collection; }

    void addMedia(Media* item) {
        collection.push_back(item);
    }

    void displayAll() {
        cout << "Library Collection:\n";
        for (auto item : collection) {
            item->displayInfo();
            cout << "-----------------\n";
        }
    }

    // Function overloading for search
    vector<Media*> search(string title) {
        vector<Media*> results;
        cout << "Search results for title '" << title << "':\n";
        for (auto item : collection) {
            if (item->getTitle() == title) {
                results.push_back(item);
                item->displayInfo();
                cout << "-----------------\n";
            }
        }
        return results;
    }

    vector<Media*> search(string attribute, string value) {
        vector<Media*> results;
        cout << "Search results for " << attribute << " '" << value << "':\n";
        for (auto item : collection) {
            Book* book = dynamic_cast<Book*>(item);
            if (book && attribute == "author" && book->getAuthor() == value) {
                results.push_back(item);
                book->displayInfo();
                cout << "-----------------\n";
                continue;
            }
            
            DVD* dvd = dynamic_cast<DVD*>(item);
            if (dvd && attribute == "director" && dvd->getDirector() == value) {
                results.push_back(item);
                dvd->displayInfo();
                cout << "-----------------\n";
                continue;
            }
            
            CD* cd = dynamic_cast<CD*>(item);
            if (cd && attribute == "artist" && cd->getArtist() == value) {
                results.push_back(item);
                cd->displayInfo();
                cout << "-----------------\n";
            }
        }
        return results;
    }

    vector<Media*> search(int year) {
        vector<Media*> results;
        cout << "Search results for publication year '" << year << "':\n";
        for (auto item : collection) {
            // Extract year from publication date (assuming format YYYY-MM-DD)
            string pubYear = item->getPublicationDate().substr(0, 4);
            if (stoi(pubYear) == year) {
                results.push_back(item);
                item->displayInfo();
                cout << "-----------------\n";
            }
        }
        return results;
    }
};

int main() {
    Library library;
    
    library.addMedia(new Book("The Great Gatsby", "1925-04-10", "B001", "Scribner", 
                            "F. Scott Fitzgerald", "9780743273565", 180));
    library.addMedia(new DVD("Inception", "2010-07-16", "D001", "Warner Bros", 
                           "Christopher Nolan", 148, "PG-13"));
    library.addMedia(new CD("Thriller", "1982-11-30", "C001", "Epic", 
                          "Michael Jackson", 9, "Pop"));
    library.addMedia(new Magazine("National Geographic", "2023-01-01", "M001", 
                                "National Geographic Society", 245, "0027-9358"));
    
    library.displayAll();
    
    cout << "\nSearch tests:\n";
    auto titleResults = library.search("Inception");
    auto authorResults = library.search("author", "F. Scott Fitzgerald");
    auto yearResults = library.search(1982);
    
    // Check out and return test using getters
    cout << "\nCheck out test:\n";
    if (!titleResults.empty()) {
        cout << "Checking out: " << titleResults[0]->getTitle() << endl;
        titleResults[0]->checkOut();
        titleResults[0]->returnItem();
    }
    
    // Demonstrate getter usage
    cout << "\nUsing getters:\n";
    const vector<Media*>& collection = library.getCollection();
    if (!collection.empty()) {
        cout << "First item in collection: " << collection[0]->getTitle() << endl;
        
        Book* book = dynamic_cast<Book*>(collection[0]);
        if (book) {
            cout << "Author: " << book->getAuthor() << endl;
            cout << "ISBN: " << book->getISBN() << endl;
        }
    }
    
    // Clean up
    for (auto item : library.getCollection()) {
        delete item;
    }
    
    return 0;
}