#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"

// customized exceptions
// trying to create a 2nd of an account that can only have 1
class TooManyOfType : public std::exception{};
// trying to withdraw money from an account without enough money in it
class BalanceTooLow : public std::exception{};
// trying to open an account with too little money in it
class OpenBalanceTooLow : public std::exception{};
// trying to use a minus value
class MinusValue : public std::exception{};

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
