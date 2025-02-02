#include <iostream>
#include <string>

typedef struct {
    int id;
    float salary;
    std::string name;
} Employee;

typedef struct {
    std::string id;
    std::string name;
    int size;
    Employee* emp;
} Organization;

int main() {
    Organization* org = new Organization {
        .id = "NUFAST123ABC",
        .name = "NU - Fast",
        .size = 123,
        .emp = new Employee {
            .id = 127,
            .salary = 400000,
            .name = "Linus Sebastian",
        }
    };

    // The question does not tell us to take input... so I didn't...
    std::cout << "The size of structure organisation: " << org->size << '\n';
    std::cout << "Organisation Name: " << org->name << '\n';
    std::cout << "Organisation Number: " << org->id << '\n';
    std::cout << "Employee id: " << org->emp->id << '\n';
    std::cout << "Employee name: " << org->emp->name << '\n';
    std::cout << "Employee Salary: " << org->emp->salary << '\n';

    delete org->emp;
    delete org;
}
