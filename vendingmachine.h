#ifndef __VENDING_MACHINE_H
#define __VENDING_MACHINE_H

#include "printer.h"

_Task VendingMachine;

#include "nameserver.h"
#include "watcard.h"

_Task VendingMachine {
    Printer &printer;
    NameServer &server;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStock;
    
    void main();
  public:
    enum Flavours { CHERRY, ROOTBEER, SEX };                 // flavours of soda (YOU DEFINE)
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
