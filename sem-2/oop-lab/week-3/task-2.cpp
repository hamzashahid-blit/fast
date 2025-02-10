#include <iostream>
#include <stdexcept>

class Date {
    int day {};
    int month {};
    int year {};
public:
    Date(int day, int month, int year) : day{day}, month{month}, year{year} {};
    void displayDate() {
        std::cout << month << '/' << day << '/' << year << '\n';
    }
};

int main(int argc, char* argv[]) {
    std::cout << "Test date: ";
    Date dateTest = Date(10, 2, 2025);
    dateTest.displayDate();

    if (argc >= 4) {
        try {
            std::cout << "Date from main args in fmt (d/m/y): ";
            Date dateMain = Date(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]));
            dateMain.displayDate();
        } catch (const std::invalid_argument& _) {
            std::cerr << "\n[ERROR] One of the date fields is not a number!\n";
        } catch (const std::out_of_range& _) {
            std::cerr << "\n[ERROR] One of the date fields is too large or too small!\n";
        }
    }
    
    return 0;
}
