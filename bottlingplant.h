#ifndef __BOTTLING_PLANT_H
#define __BOTTLING_PLANT_H

#include "printer.h"
#include "nameserver.h"

_Task BottlingPlant {
    Printer &printer;
    NameServer &server;
    
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif
