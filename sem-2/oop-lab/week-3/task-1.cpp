#include <iostream>

class User {
public:
    int age;
    std::string name;
    User(int age, std::string_view name) : age{age}, name{name} {}
};

int main() {
    User user = User(24, "Teo");
    std::cout << "My name is " << user.name << " and I'm " << user.age << " years old.\n";

    return 0;
}
