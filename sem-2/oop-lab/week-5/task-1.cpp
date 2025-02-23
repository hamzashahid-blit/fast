#include <iostream>

class Engine {
private:
    bool isRunning;

public:
    Engine() : isRunning(false) {}

    void start() {
        if (!isRunning) {
            isRunning = true;
            std::cout << "Engine started." << std::endl;
        }
    }

    void stop() {
        if (isRunning) {
            isRunning = false;
            std::cout << "Engine stopped." << std::endl;
        }
    }
};

class Car {
private:
    Engine engine;

public:
    void startCar() {
        engine.start();
    }

    void stopCar() {
        engine.stop();
    }
};

int main() {
    Car car;
    car.startCar();
    car.stopCar();
    return 0;
}
