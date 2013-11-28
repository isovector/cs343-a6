#include "watcard.h"
#include <algorithm>
using namespace std;

WATCard::WATCard() :
    balance(5)
{
}

void WATCard::deposit(unsigned int amount) {
    balance += amount;
}

void WATCard::withdraw(unsigned int amount) {
    balance -= min(amount, balance);
}

unsigned int WATCard::getBalance() {
    return balance;
}
