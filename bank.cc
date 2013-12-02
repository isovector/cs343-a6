#include "bank.h"

/*
* Constructor
*/
Bank::Bank(unsigned int numStudents) : studentAccounts(numStudents, 0)
{
}//end constructor

/*
* Deposit the specified amount in the account corrosponding to provided id
*/
void Bank::deposit(unsigned int id, unsigned int amount)
{
    studentAccounts.at(id) = studentAccounts.at(id) + amount;
}//end deposit

/*
* Withdraw the amount specified from account of provided id
*/
void Bank::withdraw(unsigned int id, unsigned int amount)
{
    while(amount > studentAccounts.at(id)) _Accept(deposit);
    studentAccounts.at(id) = studentAccounts.at(id) - amount;
}//end withdraw

