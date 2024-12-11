#include "Savings.h"

Savings::Savings(float openingAmount, bool isa) {
    this->balance = openingAmount;
    this->isa = isa;
    switch (this->isa) {
        case 0:
            this-> accountName = "Savings account";
            std::cout << "Savings account created!" << std::endl;
            break;
        case 1:
            this-> accountName = "ISA account";
            if(openingAmount < 1000) {
                throw BalanceTooLow();
            }
            std::cout << "ISA created!" << std::endl;
            break;
    }

    this->history.push_back(new Transaction("Initial deposit", openingAmount));
}

void Savings::deposit(double amount, std::string message) {
    this->balance += amount;
    this->history.push_back(new Transaction(message, amount));
    std::cout << this->toString();
}

void Savings::withdraw(double amount, std::string message) {
    if(balance - amount < 0) {
        throw BalanceTooLow();
    }
    balance -= amount;
    this->history.push_back(new Transaction(message, amount));
    std::cout << this->toString();
}

std::string Savings::toString() {
    std::stringstream ss;
    ss << this->accountName << " | " << "Balance: £" << this->balance << "\n";
    for (Transaction* t : this->history) {
        std::stringstream temp;
        temp << t->toString();
        ss << temp.str();
    }
    return ss.str();
}

float Savings::computeInterest(int time) {
    return this->balance * pow((1 + (this->interestRate/12)), 12 * time);
}

