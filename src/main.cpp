#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include "Account.h"
#include "Current.h"
#include "Savings.h"
#include "InterestEarning.h"

//Custom error exception for opening an account that already exists when only one is permitted
class TooManyOfType : public std::exception {
public:
    std::string message;

    explicit TooManyOfType(std::string message){
        this->message = "too many of account type: " + message;
    }
};

int main()
{
    std::vector <std::string> parameters;
    std::string userCommand;
    std::pmr::vector<Account*> accounts;

    std::cout << "~~~ Welcome to LincBank! ~~~" << std::endl;

    while (userCommand != "exit")
    {
        Account* stored;
        parameters.clear(); // clear ready for next command
        std::cout << std::endl << ">>>";

        std::getline(std::cin, userCommand);
        char* cstr = new char[userCommand.length() + 1];
        strcpy(cstr, userCommand.c_str());

        char* token;
        token = strtok(cstr, " ");

        while (token != NULL)
        {
            parameters.push_back(token);
            token = strtok(NULL, " ");
        }

        // Define all commands as per the brief
        std::string command = parameters[0];

        if (command.compare("options") == 0)
        {
            std::cout << "open type initial_deposit: open a current (1), savings (2) or ISA (3) account" << std::endl;
            std::cout << "view [index]: view balance and recent transactions" << std::endl;
            std::cout << "withdraw [index] sum: withdraw funds from most recently viewed account or index of account" << std::endl;
            std::cout << "deposit [index] sum: deposit funds into most recently viewed account or index of account" << std::endl;
            std::cout << "transfer src dest sum: transfer funds between accounts" << std::endl;
            std::cout << "project [index] years: project balance forward in time of most recently viewed account or index of account" << std::endl;
            std::cout << "exit: close this application" << std::endl;
            std::cout << "options: view these options again" << std::endl;
        }
        else if (command.compare("open") == 0) {
            Account* account = nullptr;
            try {
                switch (stoi(parameters[1])) {
                    case 1:
                        for (Account* account : accounts) {
                            Current* current = static_cast<Current*>(account);
                            if (current != nullptr) {
                                throw(TooManyOfType("current"));
                            }
                        }
                        account = new Current(stof(parameters[2]));
                        stored = account;
                        break;
                    case 2:
                        account = new Savings(stof(parameters[2]), false);
                        stored = account;
                        break;
                    case 3:
                        for (Account* account : accounts) {
                            Savings* save = static_cast<Savings*>(account);
                            if (save != nullptr && save->isa) {
                                throw(TooManyOfType("ISA"));
                            }
                        }
                        account = new Savings(stof(parameters[2]), true);
                        stored = account;
                        break;
                }
                accounts.push_back(account);
            }
            catch (OpenBalanceTooLow) {
                std::cout << "Failed to make account: ISA must have 1000 pound or more to open" << std::endl;
            }
            catch (TooManyOfType error) {
                std::cout << error.message << std::endl;
            }
        }
        else if (command.compare("view") == 0)
        {
            if(parameters.size() > 1) {
                std::cout << accounts[stof(parameters[1]) - 1]->toString();
                stored = accounts[stof(parameters[1]) - 1];
            }
            else{
                for(Account* a : accounts) {
                    std::cout << a->toString();
                }
            }
        }
        else if (command.compare("withdraw") == 0)
        {
            try {
                if(parameters.size() > 2) {
                    accounts[stof(parameters[1]) - 1]->withdraw(stof(parameters[2]), "withdraw");
                    stored = accounts[stof(parameters[1]) - 1];
                }
                else {
                    stored->withdraw(stof(parameters[1]), "withdraw");
                }
            }
            catch (BalanceTooLow) {
                std::cout << "not enough money in account\n";
            }
        }
        else if (command.compare("deposit") == 0)
        {
            if(parameters.size() > 2) {
                accounts[stof(parameters[1]) - 1]->deposit(stof(parameters[2]), "deposit");
                stored = accounts[stof(parameters[1]) - 1];
            }
            else {
                stored->deposit(stof(parameters[1]), "deposit");
            }
        }
        else if (command.compare("transfer") == 0)
        {
            std::stringstream ssTo;
            std::stringstream ssFrom;
            ssTo << "transfer to account " << parameters[2];
            ssFrom << "transfer from account " << parameters[1];
            try {
                accounts[stof(parameters[1]) - 1]->withdraw(stof(parameters[3]), ssTo.str());
                accounts[stof(parameters[2]) - 1]->deposit(stof(parameters[3]), ssFrom.str());
            }
            catch (BalanceTooLow) {
                std::cout << "not enough money in account";
            }


        }
        else if (command.compare("project") == 0)
        {
            Savings* save;
            if(parameters.size() == 3) {
                save = dynamic_cast<Savings*>(accounts[stof(parameters[1]) - 1]);
            }
            else {
                save = dynamic_cast<Savings*>(stored);
            }

            if (save == nullptr) {
                std::cout << "Account type does not have interest" << std::endl;
            }
            else {
                std::cout << save->computeInterest(stof(parameters[2])) << std::endl;
            }
        }
        else if (command.compare("search") == 0)
        {
            accounts[stof(parameters[1]) - 1]->search(stof(parameters[2]));
        }
    }

    std::cout << "Press any key to quit...";
    std::getchar();
}

