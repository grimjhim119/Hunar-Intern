#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<bits/stdc++.h>

using namespace std;

struct Customer {
    int id;
    string name;
    string address;
};

struct Account {
    int accountNumber;
    int customerId;
    double balance;
};

vector<Customer> customers;
vector<Account> accounts;

void loadCustomersFromFile() {
    ifstream file("customers.txt");
    Customer customer;
    while (file >> customer.id >> customer.name >> customer.address) {
        customers.push_back(customer);
    }
    file.close();
}

void saveCustomersToFile() {
    ofstream file("customers.txt");
    for (const auto& customer : customers) {
        file << customer.id << ' ' << customer.name << ' ' << customer.address << endl;
    }
    file.close();
}

void loadAccountsFromFile() {
    ifstream file("accounts.txt");
    Account account;
    while (file >> account.accountNumber >> account.customerId >> account.balance) {
        accounts.push_back(account);
    }
    file.close();
}

void saveAccountsToFile() {
    ofstream file("accounts.txt");
    for (const auto& account : accounts) {
        file << account.accountNumber << ' ' << account.customerId << ' ' << account.balance << endl;
    }
    file.close();
}

void createAccount() {
    Account account;
    cout << "Enter account number: ";
    cin >> account.accountNumber;
    cout << "Enter customer ID: ";
    cin >> account.customerId;
    account.balance = 0.0;
    accounts.push_back(account);
    saveAccountsToFile();
}

void deleteAccount() {
    int accountNumber;
    cout << "Enter account number to delete: ";
    cin >> accountNumber;
    auto it = remove_if(accounts.begin(), accounts.end(), [accountNumber](const Account& acc) {
        return acc.accountNumber == accountNumber;
    });
    accounts.erase(it, accounts.end());
    saveAccountsToFile();
}

void depositMoney() {
    int accountNumber;
    double amount;
    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    for (auto& account : accounts) {
        if (account.accountNumber == accountNumber) {
            account.balance += amount;
            saveAccountsToFile();
            cout << "Deposit successful. New balance: " << account.balance << endl;
            return;
        }
    }
    cout << "Account not found." << endl;
}

void withdrawMoney() {
    int accountNumber;
    double amount;
    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    for (auto& account : accounts) {
        if (account.accountNumber == accountNumber) {
            if (account.balance >= amount) {
                account.balance -= amount;
                saveAccountsToFile();
                cout << "Withdrawal successful. New balance: " << account.balance << endl;
            } else {
                cout << "Insufficient funds." << endl;
            }
            return;
        }
    }
    cout << "Account not found." << endl;
}

void transferMoney() {
    int fromAccount, toAccount;
    double amount;
    cout << "Enter source account number: ";
    cin >> fromAccount;
    cout << "Enter destination account number: ";
    cin >> toAccount;
    cout << "Enter amount to transfer: ";
    cin >> amount;

    Account* source = nullptr;
    Account* destination = nullptr;

    for (auto& account : accounts) {
        if (account.accountNumber == fromAccount) {
            source = &account;
        }
        if (account.accountNumber == toAccount) {
            destination = &account;
        }
    }

    if (source && destination) {
        if (source->balance >= amount) {
            source->balance -= amount;
            destination->balance += amount;
            saveAccountsToFile();
            cout << "Transfer successful." << endl;
        } else {
            cout << "Insufficient funds in source account." << endl;
        }
    } else {
        cout << "One or both accounts not found." << endl;
    }
}

void balanceInquiry() {
    int accountNumber;
    cout << "Enter account number: ";
    cin >> accountNumber;

    for (const auto& account : accounts) {
        if (account.accountNumber == accountNumber) {
            cout << "Account balance: " << account.balance << endl;
            return;
        }
    }
    cout << "Account not found." << endl;
}

void viewAllAccounts() {
    for (const auto& account : accounts) {
        cout << "Account Number: " << account.accountNumber << ", Customer ID: " << account.customerId << ", Balance: " << account.balance << endl;
    }
}

void searchAccount() {
    int accountNumber;
    cout << "Enter account number to search: ";
    cin >> accountNumber;

    for (const auto& account : accounts) {
        if (account.accountNumber == accountNumber) {
            cout << "Account found: " << account.accountNumber << ", Balance: " << account.balance << endl;
            return;
        }
    }
    cout << "Account not found." << endl;
}

void adminMenu() {
    while (true) {
        cout << "Admin Menu:\n1. View All Accounts\n2. Search Account\n3. Exit\nEnter choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                viewAllAccounts();
                break;
            case 2:
                searchAccount();
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
}

void userMenu() {
    while (true) {
        cout << "User Menu:\n1. Create Account\n2. Delete Account\n3. Deposit Money\n4. Withdraw Money\n5. Transfer Money\n6. Balance Inquiry\n7. Exit\nEnter choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deleteAccount();
                break;
            case 3:
                depositMoney();
                break;
            case 4:
                withdrawMoney();
                break;
            case 5:
                transferMoney();
                break;
            case 6:
                balanceInquiry();
                break;
            case 7:
                return;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
}

int main() {
    loadCustomersFromFile();
    loadAccountsFromFile();

    while (true) {
        cout << "Main Menu:\n1. User\n2. Admin\n3. Exit\nEnter choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                userMenu();
                break;
            case 2:
                adminMenu();
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
}
