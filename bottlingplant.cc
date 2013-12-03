#include "bottlingplant.h"
#include "truck.h"
#include "MPRNG.h"

#include <iostream>

/*
* Constructor
*/
BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments) :
    printer(prt), server(nameServer), numMachines(numVendingMachines), productionSize(maxShippedPerFlavour),
    maxStock(maxStockPerFlavour), waitTime(timeBetweenShipments), 
    hasShipment(false), done(false), production(VendingMachine::NUM_FLAVOURS)
{
}//end constructor

// helper macro to make printing so much easier.
// sure, macros are bad, but 1000x templates are probably worse in this case
#define print(state, varargs...) printer.print(Printer::BottlingPlant, state, ##varargs)

/*
* Destructor
*/
BottlingPlant::~BottlingPlant() 
{
    print('F');
}//end destructor

/*
* main
* Produce shipments
* Accepts getShipment call when shipmnet available
* Waits for truck to stop before deleting itself
*/
void BottlingPlant::main() {
    Truck truck(printer, server, *this, numMachines, maxStock);
    print('S');
    
    while (true) {
        _Accept(~BottlingPlant) {
            // listen to when we are finishing
            done = true;
            break;
        } or _When(hasShipment) _Accept(getShipment) {
            // only accept a pickup if we have a shipment
            hasShipment = false;
        } _Else {
            if (hasShipment) {
                // do nothing if we already have a shipment
                yield(0);
                continue;
            }
            
            yield(waitTime);
            
            // CREATE BOTTLES OUT OF THIN AIR
            size_t bottlesProduced = 0;
            for (size_t i = 0; i < VendingMachine::NUM_FLAVOURS; ++i) {
                production[i] = mprand(1, productionSize);
                bottlesProduced += production[i];
            }
            
            print('G', bottlesProduced);
            hasShipment = true;
        }
    }
    
    _Accept(getShipment); //Need to ensure truck gets the done message before proceding to destructor
}

/*
* Return shipment in provided array
* If the bottoling plant is shutting down then just return true
*/
bool BottlingPlant::getShipment(unsigned int cargo[]) {
    if( done == true ) {
        return true;
    }
    
    print('P');
    
    // gimme dat cargo
    for (size_t i = 0; i < VendingMachine::NUM_FLAVOURS; ++i) {
        cargo[i] = production[i];
    }
    
    return false;
}

#undef print
