// g++ -std=c++2a -Wall -Wpedantic -Werror -Wconversion

#include<iostream>
#include<vector>
#include<string>
#include<limits>
#define CAPACITY 20

int main() {
    std::vector<float> data;
    std::string value;

    for(int i = 0; i < CAPACITY; i++) {
        std::cout << "Enter value [" << i << "]: ";
        std::getline(std::cin, value);
        try {
            data.push_back(std::stof(value, nullptr));
        } catch(std::invalid_argument const& _) {
            std::cout << "Please enter a number!\n";
            i--;
        } catch(std::out_of_range const& _) {
            std::cout << "Number out of range!\n";
            i--;
        }
    }

    float* max = &data[0];
    float* second_max = &data[0];

    for(int i = 0; i < CAPACITY; i++) {
        if (data[i] > *max) {
            second_max = max;
            max = &data[i];
        }
        if (data[i] > *second_max && data[i] < *max) {
            second_max = &data[i];
        }
    }

    std::cout << "Largest: " << *max << '\n';
    std::cout << "2nd Largest: " << *second_max << '\n';
}
