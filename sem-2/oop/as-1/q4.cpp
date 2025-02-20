#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Forward declarations
class TransportCard;
class Bus;
class Route;
class Stop;

// Stop class
class Stop {
private:
    int stopID;
    string stopName;

public:
    Stop(int id, string name) : stopID(id), stopName(name) {}

    string getStopName() const {
        return stopName;
    }
};

// Route class
class Route {
private:
    int routeID;
    vector<Stop*> stops;

public:
    Route(int id) : routeID(id) {}

    void addStop(Stop* stop) {
        stops.push_back(stop);
    }

    void removeStop(int stopID) {
        for (auto it = stops.begin(); it != stops.end(); ++it) {
            if ((*it)->getStopName() == to_string(stopID)) {
                stops.erase(it);
                break;
            }
        }
    }

    vector<Stop*> getStops() const {
        return stops;
    }
};

// TransportCard class
class TransportCard {
private:
    int cardID;
    int studentID;
    bool isActive;

public:
    TransportCard(int id, int studentId) : cardID(id), studentID(studentId), isActive(false) {}

    void activateCard() {
        isActive = true;
        cout << "Card " << cardID << " activated for student " << studentID << endl;
    }

    void deactivateCard() {
        isActive = false;
        cout << "Card " << cardID << " deactivated for student " << studentID << endl;
    }

    bool checkStatus() const {
        return isActive;
    }
};

// Student class
class Student {
private:
    int studentID;
    string name;
    double balance;
    TransportCard* card;

public:
    Student(int id, string n) : studentID(id), name(n), balance(0.0), card(nullptr) {}

    void registerForTransport() {
        if (card == nullptr) {
            card = new TransportCard(studentID, studentID);
            cout << "Transport card issued for student " << studentID << endl;
        } else {
            cout << "Student already has a transport card." << endl;
        }
    }

    void payFees(double amount) {
        balance += amount;
        if (card != nullptr) {
            card->activateCard();
        }
        cout << "Payment of $" << amount << " received. New balance: $" << balance << endl;
    }

    double getBalance() const {
        return balance;
    }

    TransportCard* getTransportCard() const {
        return card;
    }

    ~Student() {
        delete card;
    }
};

// Bus class
class Bus {
private:
    int busID;
    Route* route;
    Stop* currentStop;

public:
    Bus(int id, Route* r) : busID(id), route(r), currentStop(nullptr) {}

    void addStop(Stop* stop) {
        route->addStop(stop);
    }

    void moveToNextStop() {
        auto stops = route->getStops();
        if (stops.empty()) {
            cout << "No stops available for this route." << endl;
            return;
        }

        if (currentStop == nullptr) {
            currentStop = stops[0];
        } else {
            auto it = find(stops.begin(), stops.end(), currentStop);
            if (it != stops.end() && next(it) != stops.end()) {
                currentStop = *next(it);
            } else {
                currentStop = stops[0];
            }
        }
        cout << "Bus " << busID << " moved to stop: " << currentStop->getStopName() << endl;
    }

    void recordAttendance(Student* student) {
        if (student->getTransportCard() != nullptr && student->getTransportCard()->checkStatus()) {
            cout << "Attendance recorded for student " << student->getTransportCard()->checkStatus() << " at stop " << currentStop->getStopName() << endl;
        } else {
            cout << "Student does not have an active transport card." << endl;
        }
    }
};

int main() {
    // Create stops
    Stop stop1(1, "Main Gate");
    Stop stop2(2, "Library");
    Stop stop3(3, "Cafeteria");

    // Create a route
    Route route(101);
    route.addStop(&stop1);
    route.addStop(&stop2);
    route.addStop(&stop3);

    // Create a bus
    Bus bus(201, &route);

    // Create a student
    Student student(1001, "Ali");
    student.registerForTransport();
    student.payFees(50.0);

    // Simulate bus movement and attendance recording
    bus.moveToNextStop();
    bus.recordAttendance(&student);

    bus.moveToNextStop();
    bus.recordAttendance(&student);

    return 0;
}
