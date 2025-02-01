#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<int> data;
    std::string value;

    int count = 0;
    std::cout << "Enter values of the array and type \"DONE\" when done.\n\n";
    while(true) {
        std::cout << "Enter value [" << count << "]: ";
        std::getline(std::cin, value);
        try {
            data.push_back(std::stoi(value));
            count++;
        } catch(std::invalid_argument const& _) {
            if (value == "DONE") {
                std::cout << "Exiting with " << count << " elements...\n";
                break;
            } else {
                std::cout << "Please enter a number!\n";
            }
        } catch(std::out_of_range const& _) {
            std::cout << "Number out of range!\n";
        }
    }
    
    int total = 0;
    for (int* ptr = &data[0]; ptr < data.cend().base(); ptr++) {
        total += *ptr;
    }

    std::cout << "\nTotal: " << total << '\n';
}
