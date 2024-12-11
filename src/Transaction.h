#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <sstream>
#include <ctime>
#include <iostream>

class Transaction {
public:
    Transaction(std::string desc, int value);
    std::string toString();
    std::string desc;
    std::string timestamp;
    int value;
};

#endif //TRANSACTION_H
