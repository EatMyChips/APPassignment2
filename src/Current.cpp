#include "Current.h"

// generates current account and adds all the information as well as creating a new transaction
Current::Current(float openingAmount) {
    this->balance = openingAmount;
    this-> accountName = "Current account";
    std::cout << "Current account created!" << std::endl;
    this->history.push_back(new Transaction("Initial deposit", openingAmount));
}

// adds funds to the account and creates a new transaction
void Current::deposit(double amount, std::string message) {
    this->balance += amount;
    this->history.push_back(new Transaction(message, amount));
    std::cout << this->toString();
}

// removes funds from account and checks if the funds go too low
void Current::withdraw(double amount, std::string message) {
    if(this->balance - amount < -overdraftAmount) {
        throw BalanceTooLow();
    }
    this->balance -= amount;
    this->history.push_back(new Transaction(message, amount));
    std::cout << this->toString();
}

// outputs a string with all the transactions from the account
std::string Current::toString() {
    std::stringstream ss;
    ss << this->accountName << " | " << "Balance: £" << this->balance << "\n";
    for (Transaction* t : this->history) {
        std::stringstream temp;
        temp << t->toString();
        ss << temp.str();
    }
    return ss.str();
}