#include <iostream>

class Car {
public:
    int engineHorsepower;
    int seatingCapacity;
    int noOfSpeakers;

    void setValues(int hp, int seats, int speakers) const {
        // Use const_cast to modify the values
        const_cast<Car*>(this)->engineHorsepower = hp;
        const_cast<Car*>(this)->seatingCapacity = seats;
        const_cast<Car*>(this)->noOfSpeakers = speakers;
    }

    void display() const {
        std::cout << "Engine Horsepower: " << engineHorsepower << std::endl;
        std::cout << "Seating Capacity: " << seatingCapacity << std::endl;
        std::cout << "Number of Speakers: " << noOfSpeakers << std::endl;
    }
};

int main() {
    Car car;
    car.setValues(200, 5, 4);
    car.display();
    return 0;
}
