#include <iostream>

class Account {
private:
    double balance;

public:
    Account(double initialBalance) : balance(initialBalance) {}

    void credit(double amount) {
        balance += amount;
    }

    void debit(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient balance." << std::endl;
        } else {
            balance -= amount;
        }
    }

    double getBalance() const {
        return balance;
    }
};

int main() {
    Account account(100.0);
    account.credit(50.0);
    account.debit(30.0);
    std::cout << "Current Balance: " << account.getBalance() << std::endl;
    return 0;
}
