#include "watcard.h"

WATCard::WATCard( const WATCard& ) 
{
}

WATCard &WATCard::operator=( const WATCard & )
{
}

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