#include "bank.h"

Bank::Bank( unsigned int numStudents ) : studentAccounts( numStudents, 0 )
{
}

void Bank::deposit( unsigned int id, unsigned int amount )
{
    studentAccounts.at(id) = studentAccounts.at(id) + amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount )
{
    while( amount > studentAccounts.at(id) ) _Accept( deposit );
    studentAccounts.at(id) = studentAccounts.at(id) - amount;
}

