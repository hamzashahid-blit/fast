#include <iostream>
#include <string>
#include <vector>
#include <memory>

void* sum_int_array(void* array, size_t elem_count) {
    int* total { new int{0} };
    for (size_t i = 0; i < elem_count; ++i) {
        *total += static_cast<int*>(array)[i];
    }
    return static_cast<void*>(total);
}

int main(int argc, char* argv[]) {
    std::vector<int> nums {};
    for (int i = 1; i < argc; i++) { // Skip first argument cz thats exec path
        nums.push_back(std::stoi(argv[i]));
    }

    std::unique_ptr<int> total {
        static_cast<int*>(sum_int_array(static_cast<void*>(&nums[0]), nums.size()))
    };
    
    std::cout << "Total: " << *total << '\n';
    for (size_t i = 0; i < nums.size(); i++) {
        std::cout << nums[i];
        if (i < nums.size() - 1) std::cout << ", ";
    }
    std::cout << '\n';
}
