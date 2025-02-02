#include <iostream>
#include <string>
#include <utility>
#include <vector>

typedef struct {
    int id;
    std::string name;
} Entity;

// Thank you c++11 move semantics!
std::vector<Entity> create_entities();
// I know using templates is like wayyyy overkill for this assignement
// ...but I couldnt resist the urge 😪
template <typename Comparator>
void sort_entities_by_field(std::vector<Entity>& entities, Comparator&& comparator);
void print_entities(std::vector<Entity>& entities);

int main() {
    // Low-key redditors can hate on me for using auto here, but i dont care ngl...
    auto entities = create_entities();
    std::cout << "Unsorted: ";
    print_entities(entities);
    sort_entities_by_field(entities, [](const Entity& e1, const Entity& e2) {
        return (e1.id != e2.id) ? (e1.id > e2.id) : (e1.name > e2.name);
    });
    std::cout << "Sorted: ";
    print_entities(entities);

    return 0;
}

std::vector<Entity> create_entities() {
    std::vector<Entity> entities {};
    Entity new_entity {};
    int id {};
    std::string name {};
    std::string input {};

    std::cout << "Enter entity data and type 'DONE' on the ID field when done...";
    for(int i = 0; input != "DONE"; ++i) {
        std::cout << "\nEntity [" << i << "]:\n";
        try {
            std::cout << "\tID: ";
            std::getline(std::cin, input);
            id = std::stoi(input);
            std::cout << "\tName: ";
            std::getline(std::cin, name);
            new_entity = {
                .id = id,
                .name = name,
            };
            entities.push_back(new_entity);
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

    // and well... copy elision i guess
    return entities;
}

template <typename Comparator>
void sort_entities_by_field(std::vector<Entity>& entities, Comparator&& comparator) {
    // I think I can't just use stl sort soooo... bubble sort it is i guess
    bool has_swapped { true };
    size_t sorted_count = 0;
    while (has_swapped && sorted_count != entities.size() - 1) {
        // Could use an adjacent_view but thats like c++23
        // and I dont want this to be a burden to whoever is checking this
        for (size_t i = 0; i < entities.size() - sorted_count - 1; i++) {
            if (comparator(std::forward<Entity>(entities[i]),
                           std::forward<Entity>(entities[i+1]))) {
                // Couldn't be bothered to create a template specialization
                // for Entity struct, we'll just have to use the copy constructors...
                std::swap(entities[i], entities[i+1]);
                has_swapped = true;
            }
        }
        sorted_count++;
    }
}

void print_entities(std::vector<Entity>& entities) {
    for (size_t i = 0; i < entities.size(); i++) {
        std::cout << entities[i].name << " [" << entities[i].id << ']';
        if (i != entities.size() - 1) std::cout << ", ";
    }
    std::cout << '\n';
}
