#include "watcard.h"

// nothing exciting in here. move along, move along

void WATCard::deposit( unsigned int amount )
{
    balance = balance + amount;
}

void WATCard::withdraw( unsigned int amount )
{
    if( balance > amount )
    {
        balance = balance - amount;
    }
}

unsigned int WATCard::getBalance()
{
    return balance;
}
