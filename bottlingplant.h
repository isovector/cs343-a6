#ifndef __BOTTLING_PLANT_H
#define __BOTTLING_PLANT_H

#include "printer.h"
#include "nameserver.h"

#include <vector>

_Task BottlingPlant {
    Printer &printer;
    NameServer &server;
    
    unsigned int numMachines;
    unsigned int productionSize;
    unsigned int maxStock;
    unsigned int waitTime;
    bool hasShipment;
    
    std::vector<unsigned int> production;
    
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif
