#include <iostream>
#include <string>
using namespace std;

class Account {
protected:
    int accountNumber;
    double balance;
    string ownerName;

public:
    // Default constructor
    Account() = default;

    // Parameterized constructor
    Account(int accNum, double bal, const string& name)
        : accountNumber(accNum), balance(bal), ownerName(name) {}

    // Deleted copy constructor and assignment operator
    Account(const Account&) = delete;
    Account& operator=(const Account&) = delete;

    // Deposit function
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    // Withdraw function
    bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    // Get balance
    double getBalance() const {
        return balance;
    }

    // Get account number
    int getAccountNumber() const {
        return accountNumber;
    }

    // Get owner's name
    string getOwnerName() const {
        return ownerName;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    // Parameterized constructor
    SavingsAccount(int accNum, double bal, const string& name, double rate)
        : Account(accNum, bal, name), interestRate(rate) {}

    // Calculate interest and deposit it into the account
    void calculateInterest() {
        double interest = balance * interestRate / 100;
        deposit(interest);
    }

    // Get interest rate
    double getInterestRate() const {
        return interestRate;
    }
};

int main() {
    // Usage example
    SavingsAccount savings(123456, 1000.0, "John Doe", 2.5);
    savings.deposit(500.0);
    savings.withdraw(200.0);
    savings.calculateInterest();

    cout << "Account Number: " << savings.getAccountNumber() << endl;
    cout << "Owner's Name: " << savings.getOwnerName() << endl;
    cout << "Current Balance: " << savings.getBalance() << endl;
    cout << "Interest Rate: " << savings.getInterestRate() << "%" << endl;

    return 0;
}