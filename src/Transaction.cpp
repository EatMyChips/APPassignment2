#include "Transaction.h"

// stores all the transaction information onto the object
Transaction::Transaction(std::string desc, int value){
    this->desc = desc;
    this->value = value;
    time_t date = time(NULL);
    this->timestamp = ctime(&date);
}

// outputs a string with all the transaction information
std::string Transaction::toString(){
    std::stringstream ss;
    ss << "-- " << desc << ": £" << value << " on " << timestamp;
    return ss.str();

}