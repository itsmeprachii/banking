#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class Account {
public:
    string name;
    int accNum;
    double balance;

    Account(string name, int accNum, double initialDeposit) {
        this->name = name;
        this->accNum = accNum;
        this->balance = initialDeposit;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        return true;
    }
};

class Bank {
public:
    unordered_map<int, Account> accounts;
    int accountCounter = 1000;

    void createAccount(string name, double initialDeposit) {
        int accNum = accountCounter++;
        accounts.emplace(accNum, Account(name, accNum, initialDeposit));
        cout << "Account created! Account number: " << accNum << endl;
    }

    void deposit(int accNum, double amount) {
        auto it = accounts.find(accNum);
        if (it != accounts.end()) {
            it->second.deposit(amount);
            cout << "Deposit successful! New balance: " << it->second.balance << endl;
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void withdraw(int accNum, double amount) {
        auto it = accounts.find(accNum);
        if (it != accounts.end()) {
            if (it->second.withdraw(amount)) {
                cout << "Withdrawal successful! New balance: " << it->second.balance << endl;
            } else {
                cout << "Insufficient funds!" << endl;
            }
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void transfer(int fromAcc, int toAcc, double amount) {
        auto fromIt = accounts.find(fromAcc);
        auto toIt = accounts.find(toAcc);
        if (fromIt != accounts.end() && toIt != accounts.end()) {
            if (fromIt->second.withdraw(amount)) {
                toIt->second.deposit(amount);
                cout << "Transfer successful!" << endl;
            } else {
                cout << "Insufficient funds in the source account!" << endl;
            }
        } else {
            cout << "One or both accounts not found!" << endl;
        }
    }

    void displayAccount(int accNum) {
        auto it = accounts.find(accNum);
        if (it != accounts.end()) {
            cout << "Account number: " << it->second.accNum << endl;
            cout << "Account holder: " << it->second.name << endl;
            cout << "Balance: " << it->second.balance << endl;
        } else {
            cout << "Account not found!" << endl;
        }
    }
};

int main() {
    Bank bank;
    int choice;

    while (true) {
        cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Display Account\n6. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            double initialDeposit;
            cout << "Enter account holder name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter initial deposit amount: ";
            cin >> initialDeposit;
            bank.createAccount(name, initialDeposit);
        } else if (choice == 2) {
            int accNum;
            double amount;
            cout << "Enter account number: ";
            cin >> accNum;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            bank.deposit(accNum, amount);
        } else if (choice == 3) {
            int accNum;
            double amount;
            cout << "Enter account number: ";
            cin >> accNum;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            bank.withdraw(accNum, amount);
        } else if (choice == 4) {
            int fromAcc, toAcc;
            double amount;
            cout << "Enter source account number: ";
            cin >> fromAcc;
            cout << "Enter destination account number: ";
            cin >> toAcc;
            cout << "Enter amount to transfer: ";
            cin >> amount;
            bank.transfer(fromAcc, toAcc, amount);
        } else if (choice == 5) {
            int accNum;
            cout << "Enter account number: ";
            cin >> accNum;
            bank.displayAccount(accNum);
        } else if (choice == 6) {
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
