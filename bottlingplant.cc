#include "bottlingplant.h"

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments) :
    printer(prt), server(nameServer) 
{
}

void BottlingPlant::main() {
}

bool BottlingPlant::getShipment(unsigned int cargo[]) {
    return true;
}
