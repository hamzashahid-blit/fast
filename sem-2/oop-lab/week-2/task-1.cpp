#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // Skip first argument as it is the path of the exec
    if (argc <= 1) {
        std::cerr << "Please pass atleast one argument to sum...\n";
        return -1;
    }
    
    int total {0};
    char** x_str {&argv[1]};
    char** x_end_str {&argv[argc-1]};
    while (x_str <= x_end_str) {
        total += std::stoi(*x_str);
        std::cout << *x_str;
        if (x_str != x_end_str) std::cout << " + ";
        x_str++;
    }

    std::cout << " = " << total << '\n';

    return 0;
}
