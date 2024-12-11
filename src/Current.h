#ifndef CURRENT_H
#define CURRENT_H
#include "Account.h"

class Current : public Account {
public:
    Current(float openingAmount);
    int overdraftAmount = 1000;
    void deposit(double amount, std::string message) override;
    void withdraw(double amount, std::string message) override;
    std::string toString() override;
};

#endif //CURRENT_H
