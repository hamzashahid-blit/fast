#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

int main() {
    std::string name {};
    std::vector<float> scores {};
    
    std::cout << "Please enter the name of your student followed by his test scores separated by a space:\n";
    std::string line {}, word {};
    std::getline(std::cin, line);

    std::istringstream iss {line};
    bool is_name = true;
    while (iss >> word) {
        try {
            scores.push_back(std::stof(word));
        } catch (std::invalid_argument const &_) {
            if (is_name) name += word + ' ';
            else {
                std::cerr << "[ERROR] One of the scores (" << word
                          << ") was invalid!\n";
                return -1;
            }
            continue;
        } catch (std::out_of_range const &_) {
            std::cerr << "[ERROR] One of the scores was too large!\n";
            return -1;
        }
        is_name = false;
    }

    std::cout << "Student Name: " << name << '\n';
    std::cout << "Test scores: ";
    for (float score : scores) { std::cout << score << ' '; }
    std::cout << '\n'; 
}
