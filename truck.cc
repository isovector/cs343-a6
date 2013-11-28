#include "truck.h"

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour) :
    printer(prt), server(nameServer), plant(plant)
{
}
           
void Truck::main() {
    // I'm a truck I'm a truck
    // fuck you I'm a truck
}
