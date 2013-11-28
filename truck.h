#ifndef __TRUCK_H
#define __TRUCK_H

#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"

_Task Truck {
    Printer &printer;
    NameServer &server;
    BottlingPlant &plant;
    
    void main();
    
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif
