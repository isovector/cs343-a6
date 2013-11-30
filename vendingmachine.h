#ifndef __VENDING_MACHINE_H
#define __VENDING_MACHINE_H

#include "printer.h"

_Task VendingMachine;

#include "nameserver.h"
#include "watcard.h"

#include <vector>

_Task VendingMachine {
    Printer &printer;
    NameServer &server;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStock;
    
    bool isRestocking;
    
    std::vector<unsigned int> bottles;
    
    void main();
  public:
    enum Flavours { CHERRY, CREAMSODA, ROOTBEER, LIME, NUM_FLAVOURS };
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif
