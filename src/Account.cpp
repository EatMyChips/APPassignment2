#include "Account.h"

void Account::search(int transactionAmount) {
    std::stringstream ss;
    for (Transaction* t : history) {
        if(t->value == transactionAmount) {
            ss << t->toString();
        }
    }
    std::cout << ss.str();
}