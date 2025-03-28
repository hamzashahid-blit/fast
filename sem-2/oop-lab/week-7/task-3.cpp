#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Currency {
protected:
    double amount;
    string currencyCode;
    string currencySymbol;
    double exchangeRate; // to USD

public:
    Currency(double amt, string code, string symbol, double rate = 1.0)
        : amount(amt), currencyCode(code), currencySymbol(symbol), exchangeRate(rate) {}

    virtual double convertToBase() {
        return amount * exchangeRate;
    }

    virtual double convertTo(double targetRate) {
        return amount * exchangeRate / targetRate;
    }

    virtual void displayCurrency() {
        cout << currencySymbol << amount << " (" << currencyCode << ")";
    }
};

class Dollar : public Currency {
public:
    Dollar(double amt) : Currency(amt, "USD", "$", 1.0) {}

    void displayCurrency() override {
        Currency::displayCurrency();
        cout << " (US Dollar)";
    }
};

class Euro : public Currency {
public:
    Euro(double amt) : Currency(amt, "EUR", "€", 0.93) {} // 1 USD = 0.93 EUR

    void displayCurrency() override {
        Currency::displayCurrency();
        cout << " (Euro)";
    }
};

class Rupee : public Currency {
public:
    Rupee(double amt) : Currency(amt, "INR", "₹", 82.0) {} // 1 USD = 82 INR

    void displayCurrency() override {
        Currency::displayCurrency();
        cout << " (Indian Rupee)";
    }
};

int main() {
    vector<Currency*> currencies;
    
    currencies.push_back(new Dollar(100));
    currencies.push_back(new Euro(85));
    currencies.push_back(new Rupee(5000));
    
    cout << "Currency Conversion:\n";
    for (auto curr : currencies) {
        cout << "Original: ";
        curr->displayCurrency();
        cout << "\nConverted to base (USD): $" << curr->convertToBase() << endl;
        
        // Convert to Euro
        cout << "Converted to Euro: ";
        double euroAmount = curr->convertTo(0.93);
        cout << "€" << euroAmount << endl;
        
        cout << "-----------------\n";
    }
    
    // Clean up
    for (auto curr : currencies) {
        delete curr;
    }
    
    return 0;
}