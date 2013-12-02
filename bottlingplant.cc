#include "bottlingplant.h"
#include "truck.h"
#include "MPRNG.h"

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments) :
    printer(prt), server(nameServer), numMachines(numVendingMachines), productionSize(maxShippedPerFlavour),
    maxStock(maxStockPerFlavour), waitTime(timeBetweenShipments), 
    hasShipment(false), production(VendingMachine::NUM_FLAVOURS)
{
}

#define print(state, varargs...) printer.print(Printer::BottlingPlant, state, ##varargs)

BottlingPlant::~BottlingPlant() {
    print('F');
}

void BottlingPlant::main() {
    Truck truck(printer, server, *this, numMachines, maxStock);
    
    print('S');
    
    while (true) {
        _Accept(~BottlingPlant) {
            break;
        } or _When(hasShipment) _Accept(getShipment) {
            hasShipment = false;
            print('P');
        } _Else {
            if (hasShipment) {
                yield(0);
                continue;
            }
            
            yield(waitTime);
            
            size_t bottlesProduced = 0;
            for (size_t i = 0; i < VendingMachine::NUM_FLAVOURS; ++i) {
                production[i] = mprand(1, productionSize);
                bottlesProduced += production[i];
            }
            
            print('G', bottlesProduced);
            hasShipment = true;
        }
    }
}

bool BottlingPlant::getShipment(unsigned int cargo[]) {
    for (size_t i = 0; i < VendingMachine::NUM_FLAVOURS; ++i) {
        cargo[i] = production[i];
    }
    
    return true;
}

#undef print
