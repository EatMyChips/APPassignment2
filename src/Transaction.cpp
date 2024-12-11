#include "Transaction.h"

Transaction::Transaction(std::string desc, int value){
    this->desc = desc;
    this->value = value;
    time_t date = time(NULL);
    this->timestamp = ctime(&date);
}

std::string Transaction::toString(){
    std::stringstream ss;
    ss << "-- " << desc << ": £" << value << " on " << timestamp;
    return ss.str();

}