#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"

class TooManyOfType : public std::exception{};
class BalanceTooLow : public std::exception{};

class Account {
public:
    std::pmr::vector<Transaction*> history;
    float balance = 0;
    std::string accountName;
    virtual void deposit(double amount, std::string message) = 0;
    virtual void withdraw(double amount, std::string message) = 0;
    virtual std::string toString() = 0;
    void search(int transactionAmount);
};

#endif //ACCOUNT_H
