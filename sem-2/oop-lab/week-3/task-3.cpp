#include <iostream>
#include <string>

class Glass {
    int liquid_level;
public:
    Glass() : liquid_level(200) {}
    void drink(int milliliters) {
        liquid_level = milliliters > liquid_level ? 0 : liquid_level - milliliters;
    }
    void refill() { liquid_level = 200; }
    int get_liquid_level() { return liquid_level; }
};

int main() {
    Glass glass = Glass();
    std::string input {};
    int drink_input {};
    std::cout << "Please enter how many milliliters you want to drink from the glass, and enter 'DONE' to exit...\n";
    while(true) {
        std::cout << "ml to drink: ";
        std::getline(std::cin, input);
        try {
            drink_input = std::stoi(input);
        } catch (const std::invalid_argument& _) {
            if (input == "DONE")
                break;
            std::cerr << "[ERROR] Input is not a number!\n";
            continue;
        } catch (const std::out_of_range& _) {
            std::cerr << "[ERROR] Input is too large or too small!\n";
            continue;
        }
        if (drink_input <= 0) {
            std::cout << "[ERROR] Cannot drink zero or less milliliters!\n";
            continue;
        }
        std::cout << "Attempting to drink " << drink_input << "ml...\n";
        glass.drink(drink_input);
        std::cout << "Glass now has " << glass.get_liquid_level() << "ml\n";
        if (glass.get_liquid_level() < 100) {
            std::cout << "Refilling glass to 200ml...\n";
            glass.refill();
        }
    }

    std::cout << "Glass has " << glass.get_liquid_level() << "ml\n";
    
    return 0;
}
