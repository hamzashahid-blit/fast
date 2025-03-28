#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account {
protected:
    string accountNumber;
    double balance;
    string accountHolderName;
    string accountType;

public:
    Account(string num, double bal, string name, string type = "Generic")
        : accountNumber(num), balance(bal), accountHolderName(name), accountType(type) {}

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposited $" << amount << " to account " << accountNumber << endl;
    }

    virtual void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds in account " << accountNumber << endl;
        } else {
            balance -= amount;
            cout << "Withdrew $" << amount << " from account " << accountNumber << endl;
        }
    }

    virtual double calculateInterest() {
        return 0.0; // Base account has no interest
    }

    virtual void printStatement() {
        cout << "Account Statement for " << accountNumber << "\n"
             << "Holder: " << accountHolderName << "\n"
             << "Type: " << accountType << "\n"
             << "Balance: $" << balance << "\n";
    }

    virtual void getAccountInfo() {
        cout << "Account Info:\n"
             << "Number: " << accountNumber << "\n"
             << "Holder: " << accountHolderName << "\n"
             << "Type: " << accountType << "\n"
             << "Balance: $" << balance << "\n";
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;
    double minimumBalance;

public:
    SavingsAccount(string num, double bal, string name, double rate, double minBal)
        : Account(num, bal, name, "Savings"), interestRate(rate), minimumBalance(minBal) {}

    double calculateInterest() override {
        double interest = balance * interestRate / 100;
        balance += interest;
        return interest;
    }

    void withdraw(double amount) override {
        if (balance - amount < minimumBalance) {
            cout << "Cannot withdraw. Minimum balance requirement not met for account " << accountNumber << endl;
        } else {
            Account::withdraw(amount);
        }
    }

    void printStatement() override {
        Account::printStatement();
        cout << "Interest Rate: " << interestRate << "%\n"
             << "Minimum Balance: $" << minimumBalance << "\n";
    }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(string num, double bal, string name)
        : Account(num, bal, name, "Checking") {}

    void printStatement() override {
        Account::printStatement();
        cout << "No interest on checking accounts\n";
    }
};

class FixedDepositAccount : public Account {
private:
    string maturityDate;
    double fixedInterestRate;

public:
    FixedDepositAccount(string num, double bal, string name, string date, double rate)
        : Account(num, bal, name, "Fixed Deposit"), maturityDate(date), fixedInterestRate(rate) {}

    double calculateInterest() override {
        double interest = balance * fixedInterestRate / 100;
        balance += interest;
        return interest;
    }

    void withdraw(double amount) override {
        cout << "Cannot withdraw from Fixed Deposit account " << accountNumber 
             << " before maturity date " << maturityDate << endl;
    }

    void printStatement() override {
        Account::printStatement();
        cout << "Maturity Date: " << maturityDate << "\n"
             << "Fixed Interest Rate: " << fixedInterestRate << "%\n";
    }
};

int main() {
    vector<Account*> accounts;
    
    accounts.push_back(new SavingsAccount("SA001", 1000, "Alice", 2.5, 500));
    accounts.push_back(new CheckingAccount("CA001", 2000, "Bob"));
    accounts.push_back(new FixedDepositAccount("FD001", 5000, "Charlie", "2025-12-31", 5.0));
    
    for (auto acc : accounts) {
        acc->deposit(500);
        acc->withdraw(200);
        acc->calculateInterest();
        acc->printStatement();
        cout << "-----------------\n";
    }
    
    // Clean up
    for (auto acc : accounts) {
        delete acc;
    }
    
    return 0;
}