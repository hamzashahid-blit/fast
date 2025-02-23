#include <iostream>

class Student {
private:
    const int rollNo;

public:
    Student(int roll) : rollNo(roll) {}

    void display() const {
        std::cout << "Roll No: " << rollNo << std::endl;
    }
};

int main() {
    int roll;
    std::cout << "Enter Roll No: ";
    std::cin >> roll;

    Student student(roll);
    student.display();

    return 0;
}
