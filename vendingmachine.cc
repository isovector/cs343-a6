#include "vendingmachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                unsigned int maxStockPerFlavour) :
    printer(prt), server(nameServer), id(id), sodaCost(sodaCost), maxStock(maxStockPerFlavour)
{
}

void VendingMachine::main() {
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {
    return BUY;
}

unsigned int* VendingMachine::inventory() {
    return NULL;
}

void VendingMachine::restocked() {
}

unsigned int VendingMachine::cost() {
    return sodaCost;
}

unsigned int VendingMachine::getId() {
    return id;
}
