#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Vehicle class
class Vehicle {
private:
    string model;
    double rentalPricePerDay;
    string requiredLicenseType;

public:
    Vehicle(string m, double price, string licenseType)
        : model(m), rentalPricePerDay(price), requiredLicenseType(licenseType) {}

    string getModel() const { return model; }
    double getRentalPricePerDay() const { return rentalPricePerDay; }
    string getRequiredLicenseType() const { return requiredLicenseType; }

    void displayDetails() const {
        cout << "Model: " << model << endl;
        cout << "Rental Price Per Day: $" << rentalPricePerDay << endl;
        cout << "Required License Type: " << requiredLicenseType << endl;
    }
};

// User class
class User {
private:
    string userId;
    string name;
    int age;
    string contactNumber;
    string licenseType;

public:
    User(string id, string n, int a, string contact, string license)
        : userId(id), name(n), age(a), contactNumber(contact), licenseType(license) {}

    void updateDetails(string newName, int newAge, string newContact, string newLicenseType) {
        name = newName;
        age = newAge;
        contactNumber = newContact;
        licenseType = newLicenseType;
    }

    string getUserId() const { return userId; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getContactNumber() const { return contactNumber; }
    string getLicenseType() const { return licenseType; }

    void displayDetails() const {
        cout << "User ID: " << userId << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Contact Number: " << contactNumber << endl;
        cout << "License Type: " << licenseType << endl;
    }
};

// RentalSystem class
class RentalSystem {
private:
    vector<User> users;
    vector<Vehicle*> vehicles;

public:
    ~RentalSystem() {
        for (auto vehicle : vehicles) {
            delete vehicle;
        }
    }

    void registerUser() {
        string userId, name, contactNumber, licenseType;
        int age;

        cout << "Enter User ID: ";
        cin >> userId;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Contact Number: ";
        cin >> contactNumber;
        cout << "Enter License Type (Learner/Intermediate/Full): ";
        cin >> licenseType;

        users.push_back(User(userId, name, age, contactNumber, licenseType));
        cout << "User registered successfully!" << endl;
    }

    void updateUserDetails() {
        string userId;
        cout << "Enter User ID to update details: ";
        cin >> userId;

        for (auto& user : users) {
            if (user.getUserId() == userId) {
                string newName, newContact, newLicenseType;
                int newAge;

                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter New Age: ";
                cin >> newAge;
                cout << "Enter New Contact Number: ";
                cin >> newContact;
                cout << "Enter New License Type (Learner/Intermediate/Full): ";
                cin >> newLicenseType;

                user.updateDetails(newName, newAge, newContact, newLicenseType);
                cout << "User details updated successfully!" << endl;
                return;
            }
        }
        cout << "User not found!" << endl;
    }

    void addVehicle() {
        string model, requiredLicenseType;
        double rentalPricePerDay;

        cout << "Enter Vehicle Model: ";
        cin.ignore();
        getline(cin, model);
        cout << "Enter Rental Price Per Day: ";
        cin >> rentalPricePerDay;
        cout << "Enter Required License Type (Learner/Intermediate/Full): ";
        cin >> requiredLicenseType;

        vehicles.push_back(new Vehicle(model, rentalPricePerDay, requiredLicenseType));
        cout << "Vehicle added successfully!" << endl;
    }

    void displayAvailableVehicles() const {
        cout << "Available Vehicles:" << endl;
        for (const auto& vehicle : vehicles) {
            vehicle->displayDetails();
            cout << "-------------------------" << endl;
        }
    }

    void rentVehicle() {
        string userId;
        cout << "Enter User ID to rent a vehicle: ";
        cin >> userId;

        for (auto& user : users) {
            if (user.getUserId() == userId) {
                displayAvailableVehicles();

                string model;
                cout << "Enter the model of the vehicle you want to rent: ";
                cin.ignore();
                getline(cin, model);

                for (const auto& vehicle : vehicles) {
                    if (vehicle->getModel() == model) {
                        if (user.getLicenseType() == vehicle->getRequiredLicenseType()) {
                            cout << "Rental successful!" << endl;
                            cout << "Vehicle Details:" << endl;
                            vehicle->displayDetails();
                            return;
                        } else {
                            cout << "You are not eligible to rent this vehicle. Required License Type: "
                                 << vehicle->getRequiredLicenseType() << endl;
                            return;
                        }
                    }
                }
                cout << "Vehicle not found!" << endl;
                return;
            }
        }
        cout << "User not found!" << endl;
    }
};

int main() {
    RentalSystem rentalSystem;
    int choice;

    do {
        cout << "\nVehicle Rental System Menu:" << endl;
        cout << "1. Register User" << endl;
        cout << "2. Update User Details" << endl;
        cout << "3. Add Vehicle" << endl;
        cout << "4. Display Available Vehicles" << endl;
        cout << "5. Rent Vehicle" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                rentalSystem.registerUser();
                break;
            case 2:
                rentalSystem.updateUserDetails();
                break;
            case 3:
                rentalSystem.addVehicle();
                break;
            case 4:
                rentalSystem.displayAvailableVehicles();
                break;
            case 5:
                rentalSystem.rentVehicle();
                break;
            case 6:
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
