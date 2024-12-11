#include "Current.h"

Current::Current(float openingAmount) {
    this->balance = openingAmount;
    this-> accountName = "Current account";
    std::cout << "Current account created!" << std::endl;
    this->history.push_back(new Transaction("Initial deposit", openingAmount));
}

void Current::deposit(double amount, std::string message) {
    this->balance += amount;
    this->history.push_back(new Transaction(message, amount));
    std::cout << this->toString();
}

void Current::withdraw(double amount, std::string message) {
    if(this->balance - amount < -overdraftAmount) {
        throw BalanceTooLow();
    }
    this->balance -= amount;
    this->history.push_back(new Transaction(message, amount));
    std::cout << this->toString();
}

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