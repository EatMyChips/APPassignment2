#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include "Account.h"
#include "Current.h"
#include "Savings.h"
#include "InterestEarning.h"

int main()
{
    std::vector <std::string> parameters;
    std::string userCommand;
    std::pmr::vector<Account*> accounts;
    std::pmr::vector<Savings*> saveAccounts;
    // you may also want to store a collection of opened accounts here

    std::cout << "~~~ Welcome to LincBank! ~~~" << std::endl;

    while (userCommand != "exit")
    {
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
            // display the various commands to the user
        }
        else if (command.compare("open") == 0) {
            Account* account = nullptr;
            try {
                switch (stoi(parameters[1])) {
                    case 1:
                        account = new Current(stof(parameters[2]));
                        break;
                    case 2:
                        account = new Savings(stof(parameters[2]), false);
                        //saveAccounts.push_back(account);
                        break;
                    case 3:
                        account = new Savings(stof(parameters[2]), true);
                        //saveAccounts.push_back(account);
                        break;
                }
                accounts.push_back(account);
            }
            catch (BalanceTooLow) {
                std::cout << "failed to make account\n";
            }
        }
        else if (command.compare("view") == 0)
        {
            if(parameters.size() > 1) {
                std::cout << accounts[stof(parameters[1]) - 1]->toString();
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
                accounts[stof(parameters[1]) - 1]->withdraw(stof(parameters[2]), "withdraw");
            }
            catch (BalanceTooLow) {
                std::cout << "not enough money in account\n";
            }
        }
        else if (command.compare("deposit") == 0)
        {
            accounts[stof(parameters[1]) - 1]->deposit(stof(parameters[2]), "deposit");
        }
        else if (command.compare("transfer") == 0)
        {
            std::stringstream ssTo;
            std::stringstream ssFrom;
            ssTo << "transfer to account " << parameters[2];
            ssFrom << "transfer from account " << parameters[1];
            try {
                accounts[stof(parameters[1]) - 1]->withdraw(stof(parameters[3]), ssTo.str());
            }
            catch (BalanceTooLow) {
                std::cout << "not enough money in account";
            }

            accounts[stof(parameters[2]) - 1]->deposit(stof(parameters[3]), ssFrom.str());
        }
        else if (command.compare("project") == 0)
        {
            //accounts[stof(parameters[1])]->computeInterest();
        }
        else if (command.compare("search") == 0)
        {
            accounts[stof(parameters[1]) - 1]->search(stof(parameters[2]));
        }
    }

    std::cout << "Press any key to quit...";
    std::getchar();
}

