#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    int capacity { 5 };
    int actual_capacity {};
    int* arr { static_cast<int*>(malloc(capacity * sizeof(int))) };

    std::cout << "Please enter a list of numbers and type 'DONE' once done...\n";
    std::string input {};
    for(int i = 0; input != "DONE"; ++i) {
        if (i + 1 > capacity) {
            std::cout << "Reallocating size from " << capacity;
            capacity *= 2;
            std::cout << " to " << capacity << '\n';
            arr = static_cast<int*>(realloc(arr, capacity * sizeof(int)));
        }
        std::cout << "Element [" << i << "]: ";
        try {
            std::getline(std::cin, input);
            arr[i] = std::stoi(input);
        } catch (std::invalid_argument const &ex) {
            i--;
            if (input != "DONE") {
                std::cerr << "[ERROR] Please enter a number!\n";
            }
            continue;
        } catch (std::out_of_range const &ex) {
            i--;
            std::cerr << "[ERROR] Number was too large!\n";
            continue;
        }
        actual_capacity++;
    }

    if (actual_capacity != capacity) {
        std::cout << "Reallocating size from " << capacity << " to " << actual_capacity << "...\n";
        arr = static_cast<int*>(realloc(arr, actual_capacity * sizeof(int)));
        capacity = actual_capacity;
    }

    for (int i = 0; i < capacity; i++) {
        std::cout << arr[i];
        if (i != capacity - 1) std::cout << ", ";
        else std::cout << '\n';
    }

    delete[] arr;
}
