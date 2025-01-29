#include <iostream>
#include <iomanip>
#include <string>

int main() {
    std::string curr_input;

    std::cout << "Please enter customer ID: ";
    std::getline(std::cin, curr_input);
    int id {std::stoi(curr_input)};

    std::cout << "Please enter customer's first name: ";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "Please enter units consumed: ";
    std::getline(std::cin, curr_input);
    int consumed {std::stoi(curr_input)};

    if (consumed < 0 || id < 0) {
        std::cout << "Consumed units and ID cannot be negative!\n";
        return -1;
    }
    
    float unit_price {35.90f};
    if (consumed < 200) unit_price = 16.20f;
    else if (consumed < 300) unit_price = 20.10f;
    else if (consumed < 500) unit_price = 27.10f;

    float bill {unit_price * static_cast<float>(consumed)};
    if (bill > 18000) bill *= 1.15f;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nAmount Charges With Unit Price @Rs. " << unit_price << ": " << bill / 1.15 << '\n';
    std::cout << "Surcharge Amount: " << bill - (bill / 1.15) << '\n';
    std::cout << "Net Amount to be Paid by The Customer: " << bill << '\n';
    
    return 0;
}
