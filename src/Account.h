#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"

// customized exceptions
// trying to withdraw money from an account without enough money in it
class BalanceTooLow : public std::exception {
public:
    float maxWithdraw = 0.0f;

    explicit BalanceTooLow(const float balance) {
        this->maxWithdraw = balance;
    }
};

// trying to open an account with too little money in it
class OpenBalanceTooLow : public std::exception {};


class Account {
public:
    std::vector<Transaction*> history;
    float balance = 0;
    std::string accountName;
    virtual void deposit(double amount, std::string message) = 0;
    virtual void withdraw(double amount, std::string message) = 0;
    virtual std::string toString() = 0;
    void search(int transactionAmount);
};

#endif //ACCOUNT_H
