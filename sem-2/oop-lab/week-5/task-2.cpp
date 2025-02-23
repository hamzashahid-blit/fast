#include <iostream>
#include <vector>

class Car {
public:
    std::string name;
    int id;

    Car(std::string n, int i) : name(n), id(i) {}
};

class Garage {
private:
    std::vector<Car*> cars;

public:
    void parkCar(Car* car) {
        cars.push_back(car);
    }

    void listCars() {
        for (const auto& car : cars) {
            std::cout << "Car ID: " << car->id << ", Name: " << car->name << std::endl;
        }
    }
};

int main() {
    Car car1("Toyota", 1);
    Car car2("Honda", 2);

    Garage garage;
    garage.parkCar(&car1);
    garage.parkCar(&car2);

    garage.listCars();

    return 0;
}
