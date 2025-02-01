#include <iostream>
#include <iomanip>
#include <string>

int main() {
    std::string weight_kg_str;
    std::cout << "Please enter your weight in kilograms: ";
    std::getline(std::cin, weight_kg_str);
    float weight_lb {std::stof(weight_kg_str) * 2.205f};
    std::cout << "Your weight in pounds: " << std::fixed << std::setprecision(2) << weight_lb << '\n';
}
