#include <iostream>
#include <string>

// Base class for Vehicles
class Vehicles {
private:
    double price; // Price of the vehicle

public:
    // Constructor to initialize price
    Vehicles(double vehiclePrice) : price(vehiclePrice) {}

    // Getter for price
    double getPrice() const {
        return price;
    }

    // Virtual function to display vehicle details (to be overridden by derived classes)
    virtual void displayDetails() const = 0; // Pure virtual function to make Vehicles an abstract class
};

// Derived class for Car
class Car : public Vehicles {
private:
    int seatingCapacity; // Seating capacity of the car
    int numberOfDoors;   // Number of doors in the car
    std::string fuelType; // Fuel type of the car (petrol or diesel)

public:
    // Constructor to initialize Car details
    Car(double carPrice, int capacity, int doors, const std::string& fuel)
        : Vehicles(carPrice), seatingCapacity(capacity), numberOfDoors(doors), fuelType(fuel) {}

    // Getter methods for Car-specific details
    int getSeatingCapacity() const {
        return seatingCapacity;
    }

    int getNumberOfDoors() const {
        return numberOfDoors;
    }

    std::string getFuelType() const {
        return fuelType;
    }

    // Override displayDetails to show Car-specific details
    void displayDetails() const override {
        std::cout << "Price: $" << getPrice() << std::endl;
        std::cout << "Seating Capacity: " << seatingCapacity << std::endl;
        std::cout << "Number of Doors: " << numberOfDoors << std::endl;
        std::cout << "Fuel Type: " << fuelType << std::endl;
    }
};

// Derived class for Motorcycle
class Motorcycle : public Vehicles {
private:
    int numberOfCylinders; // Number of cylinders in the motorcycle
    int numberOfGears;     // Number of gears in the motorcycle
    int numberOfWheels;    // Number of wheels in the motorcycle

public:
    // Constructor to initialize Motorcycle details
    Motorcycle(double bikePrice, int cylinders, int gears, int wheels)
        : Vehicles(bikePrice), numberOfCylinders(cylinders), numberOfGears(gears), numberOfWheels(wheels) {}

    // Getter methods for Motorcycle-specific details
    int getNumberOfCylinders() const {
        return numberOfCylinders;
    }

    int getNumberOfGears() const {
        return numberOfGears;
    }

    int getNumberOfWheels() const {
        return numberOfWheels;
    }

    // Override displayDetails to show Motorcycle-specific details
    void displayDetails() const override {
        std::cout << "Price: $" << getPrice() << std::endl;
        std::cout << "Number of Cylinders: " << numberOfCylinders << std::endl;
        std::cout << "Number of Gears: " << numberOfGears << std::endl;
        std::cout << "Number of Wheels: " << numberOfWheels << std::endl;
    }
};

// Derived class for Audi (subclass of Car)
class Audi : public Car {
private:
    std::string modelType; // Model type of the Audi car

public:
    // Constructor to initialize Audi details
    Audi(double price, int capacity, int doors, const std::string& fuel, const std::string& model)
        : Car(price, capacity, doors, fuel), modelType(model) {}

    // Override displayDetails to show Audi-specific details
    void displayDetails() const override {
        std::cout << "Audi Car Details:" << std::endl;
        Car::displayDetails(); // Call base class displayDetails
        std::cout << "Model Type: " << modelType << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
};

// Derived class for Yamaha (subclass of Motorcycle)
class Yamaha : public Motorcycle {
private:
    std::string makeType; // Make type of the Yamaha motorcycle

public:
    // Constructor to initialize Yamaha details
    Yamaha(double price, int cylinders, int gears, int wheels, const std::string& make)
        : Motorcycle(price, cylinders, gears, wheels), makeType(make) {}

    // Override displayDetails to show Yamaha-specific details
    void displayDetails() const override {
        std::cout << "Yamaha Motorcycle Details:" << std::endl;
        Motorcycle::displayDetails(); // Call base class displayDetails
        std::cout << "Make Type: " << makeType << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
};

int main() {
    // Create objects of Audi and Yamaha
    Audi audi(50000, 5, 4, "Petrol", "A4");
    Yamaha yamaha(15000, 2, 5, 2, "YZF-R1");

    // Display details of the Audi car and Yamaha motorcycle
    audi.displayDetails();
    yamaha.displayDetails();

    return 0;
}
