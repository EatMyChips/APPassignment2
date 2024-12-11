#ifndef SAVINGS_H
#define SAVINGS_H
#include "Account.h"
#include "InterestEarning.h"
#include <cmath>


class Savings : public Account, public InterestEarning {
public:
    Savings(float openingAmount, bool isa);
    float interestRate;
    bool isa;
    float computeInterest(int time) override;
    void deposit(double amount, std::string message) override;
    void withdraw(double amount, std::string message) override;
    std::string toString() override;
};

#endif //SAVINGS_H
