#include "truck.h"
#include "MPRNG.h"
using namespace std;

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour) :
    printer(prt), server(nameServer), plant(plant), numMachines(numVendingMachines), maxStock(maxStockPerFlavour)
{
}

#define print(state, varargs...) printer.print(Printer::Truck, state, ##varargs)

void Truck::main() {
    VendingMachine **machines = server.getMachineList();
    size_t bottlesRemaining = 0;
    vector<unsigned int> shipment(VendingMachine::NUM_FLAVOURS);
    
    print('S');
    
    while (true) {
        yield(mprand(1, 10));
        if (plant.getShipment(&shipment[0])) {
            // plant is shutting down.
            // super weird return value, but #yolo
            break;
        }
        
        bottlesRemaining = 0;
        for (size_t f = 0; f < VendingMachine::NUM_FLAVOURS; ++f) {
            bottlesRemaining += shipment[f];
        }
        
        print('P', bottlesRemaining);
        
        for (size_t v = 0; v < numMachines && bottlesRemaining > 0; ++v) {
            VendingMachine &machine = *machines[v];
            unsigned int *inventory = machine.inventory();
            
            print('d', machine.getId(), bottlesRemaining);
            
            for (size_t f = 0; f < VendingMachine::NUM_FLAVOURS && bottlesRemaining > 0; ++f) {
                // TODO: there is a failure condition here but i dont know how it works
                while (inventory[f] < maxStock && shipment[f] > 0) {
                    ++inventory[f];
                    --shipment[f];
                    --bottlesRemaining;
                }
            }
            
            machine.restocked();
            print('D', machine.getId(), bottlesRemaining);
        }
    }
    
    print('F');
}

#undef print
