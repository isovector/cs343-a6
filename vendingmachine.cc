#include "vendingmachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                unsigned int maxStockPerFlavour) :
    printer(prt), server(nameServer), id(id), sodaCost(sodaCost), maxStock(maxStockPerFlavour), isRestocking(false)
{
    for (size_t i = 0; i < NUM_FLAVOURS; ++i) {
        bottles.push_back(0);
    }
}

// helper printer
#define print(state, varargs...) printer.print(Printer::Vending, id, state, ##varargs)

VendingMachine::~VendingMachine() {
    print('F');
}

void VendingMachine::main() {
    print('S', sodaCost);
    
    while (true) {
        _Accept(~VendingMachine) {
            break;
        } 
        // can't use me 'cause i'm restocking, silly
        or _When(!isRestocking) _Accept(buy) {
        }
        or _Accept(inventory) {
            print('r');
            isRestocking = true;
        }
        or _Accept(restocked) {
            print('R');
            isRestocking = false;
        }
    }
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {
    // you want what?
    size_t idx = static_cast<size_t>(flavour);
    
    if (bottles[idx] == 0) {
        // don't have any, sorry
        return STOCK;
    } else if (card.getBalance() < sodaCost) {
        // you're poor. get more dollars
        return FUNDS;
    }
    
    // manage inventory and cash
    --bottles[idx];
    card.withdraw(sodaCost);
    
    print('B', idx, bottles[idx]);
    
    return BUY;
}

unsigned int* VendingMachine::inventory() {
    // vector to array, totally cool right?
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

#undef print
