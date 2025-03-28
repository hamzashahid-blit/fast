#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

constexpr double M_PI = 3.1415;

class Shape {
protected:
    pair<double, double> position;
    string color;
    double borderThickness;

public:
    Shape(double x, double y, string col, double thickness = 1.0)
        : position(make_pair(x, y)), color(col), borderThickness(thickness) {}

    virtual void draw() {
        cout << "Drawing a generic shape at (" << position.first << ", " 
             << position.second << ") with color " << color << endl;
    }

    virtual double calculateArea() {
        return 0.0;
    }

    virtual double calculatePerimeter() {
        return 0.0;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double x, double y, double r, string col, double thickness = 1.0)
        : Shape(x, y, col, thickness), radius(r) {}

    void draw() override {
        cout << "Drawing a circle at (" << position.first << ", " << position.second 
             << ") with radius " << radius << " and color " << color << endl;
    }

    double calculateArea() override {
        return M_PI * radius * radius;
    }

    double calculatePerimeter() override {
        return 2 * M_PI * radius;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double x, double y, double w, double h, string col, double thickness = 1.0)
        : Shape(x, y, col, thickness), width(w), height(h) {}

    void draw() override {
        cout << "Drawing a rectangle at (" << position.first << ", " << position.second 
             << ") with width " << width << ", height " << height << " and color " << color << endl;
    }

    double calculateArea() override {
        return width * height;
    }

    double calculatePerimeter() override {
        return 2 * (width + height);
    }
};

class Triangle : public Shape {
private:
    double side1, side2, side3;

public:
    Triangle(double x, double y, double s1, double s2, double s3, string col, double thickness = 1.0)
        : Shape(x, y, col, thickness), side1(s1), side2(s2), side3(s3) {}

    void draw() override {
        cout << "Drawing a triangle at (" << position.first << ", " << position.second 
             << ") with sides " << side1 << ", " << side2 << ", " << side3 
             << " and color " << color << endl;
    }

    double calculateArea() override {
        // Using Heron's formula
        double s = (side1 + side2 + side3) / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    double calculatePerimeter() override {
        return side1 + side2 + side3;
    }
};

int main() {
    vector<Shape*> shapes;
    
    shapes.push_back(new Circle(10, 10, 5, "red"));
    shapes.push_back(new Rectangle(20, 20, 8, 6, "blue"));
    shapes.push_back(new Triangle(30, 30, 3, 4, 5, "green"));
    
    for (auto shape : shapes) {
        shape->draw();
        cout << "Area: " << shape->calculateArea() << endl;
        cout << "Perimeter: " << shape->calculatePerimeter() << endl;
        cout << "-----------------\n";
    }
    
    // Clean up
    for (auto shape : shapes) {
        delete shape;
    }
    
    return 0;
}