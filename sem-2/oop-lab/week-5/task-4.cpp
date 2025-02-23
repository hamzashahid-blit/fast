#include <iostream>
#include <thread>
#include <chrono>

class Blend {
public:
    void blendJuice() {
        std::cout << "Blending juice..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(4));
        std::cout << "Juice blended." << std::endl;
    }
};

class Grind {
public:
    void grindJuice() {
        std::cout << "Grinding juice..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Juice ground." << std::endl;
    }
};

class JuiceMaker {
private:
    Blend blend;
    Grind grind;

public:
    void makeJuice() {
        blend.blendJuice();
        grind.grindJuice();
    }
};

int main() {
    JuiceMaker maker;
    maker.makeJuice();
    return 0;
}
