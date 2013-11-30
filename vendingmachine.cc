#include "vendingmachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                unsigned int maxStockPerFlavour) :
    printer(prt), server(nameServer), id(id), sodaCost(sodaCost), maxStock(maxStockPerFlavour), isRestocking(false)
{
    for (size_t i = 0; i < NUM_FLAVOURS; ++i) {
        bottles.push_back(0);
    }
}

void VendingMachine::main() {
    while (true) {
        _Accept(~VendingMachine) {
            break;
        } or _When(!isRestocking) _Accept(buy) {
        } or _Accept(inventory) {
            isRestocking = true;
        } or _Accept(restocked) {
            isRestocking = false;
        }
    }
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {
    size_t idx = static_cast<size_t>(flavour);
    if (bottles[idx] == 0) {
        return STOCK;
    } else if (card.getBalance() < sodaCost) {
        return FUNDS;
    }
    
    --bottles[idx];
    card.withdraw(sodaCost);
    return BUY;
}

unsigned int* VendingMachine::inventory() {
    return &bottles[0];
}

void VendingMachine::restocked() {
}

unsigned int VendingMachine::cost() {
    return sodaCost;
}

unsigned int VendingMachine::getId() {
    return id;
}
