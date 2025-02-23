#include <iostream>
#include <cmath>

class Circle {
private:
    double radius;
    const double PI = 3.14159;

public:
    Circle(double r) : radius(r) {}

    double getArea() const {
        return PI * pow(radius, 2);
    }

    double getPerimeter() const {
        return 2 * PI * radius;
    }
};

int main() {
    Circle circle(5.0);
    std::cout << "Area: " << circle.getArea() << std::endl;
    std::cout << "Perimeter: " << circle.getPerimeter() << std::endl;
    return 0;
}
