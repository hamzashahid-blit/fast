#include <iostream>
#include <string>
#include <vector>

typedef struct {
    std::string subject;
} Inner;

typedef struct {
    int id;
    std::vector<Inner> inners;
} Outer;

int main() {
    std::vector<Outer> outers {};
    std::vector<Inner> inners {};
    Outer new_outer {};
    int id {};
    std::string subject {};
    std::string input {};
    
    std::cout << "Enter outer data and type 'DONE' on the ID field when done...";
    for(int i = 0; input != "DONE"; ++i) {
        inners.clear();
        subject = "";
        std::cout << "\nOuter [" << i << "]:\n";
        try {
            std::cout << "\tID: ";
            std::getline(std::cin, input);
            id = std::stoi(input);
            for(int j = 0; subject != "DONE"; ++j) {
                std::cout << "\tSubject [" << j << "]: ";
                std::getline(std::cin, subject);
                inners.push_back(Inner { subject });
            }
            new_outer = {
                .id = id,
                .inners = inners,
            };
            outers.push_back(new_outer);
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
    }

    for (size_t i = 0; i < outers.size(); i++) {
        std::cout << outers[i].id << " [";
        for (size_t j = 0; j < outers[i].inners.size(); j++) {
            std::cout << outers[i].inners[j].subject;
            if (j != outers[i].inners.size() - 1) std::cout << ", ";
        }
        std::cout << ']';
        if (i != outers.size() - 1) std::cout << ", ";
    }
    
    std::cout << '\n';
    return 0;
}
