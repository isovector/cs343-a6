#include "truck.h"
#include "MPRNG.h"
using namespace std;

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour) :
    printer(prt), server(nameServer), plant(plant), numMachines(numVendingMachines), maxStock(maxStockPerFlavour)
{
}

#define print(state, varargs...) printer.print(Printer::Truck, state, ##varargs)
Truck::~Truck()
{
    print('F');
}


void Truck::main() {
    VendingMachine **machines = server.getMachineList();
    size_t bottlesRemaining = 0;
    vector<unsigned int> shipment(VendingMachine::NUM_FLAVOURS);
    
    print('S');
    
    while (true) 
    {
        _Accept( ~Truck )
        {
            break;
        }
        _Else
        {
            yield(mprand(1, 10));
            if(plant.getShipment(&shipment[0])) 
            {
                // plant is shutting down.
                // super weird return value, but #yolo
                break;
            }
            
            bottlesRemaining = 0;
            for(size_t f = 0; f < VendingMachine::NUM_FLAVOURS; ++f) 
            {
                bottlesRemaining += shipment[f];
            }
            
            print('P', bottlesRemaining);
            
            for (size_t v = 0; v < numMachines && bottlesRemaining > 0; v++) 
            {
                VendingMachine &machine = *machines[v];
                unsigned int *inventory = machine.inventory();
                print('d', machine.getId(), bottlesRemaining);
                size_t unfilledVendingMachine = 0;
                for (size_t f = 0; f < VendingMachine::NUM_FLAVOURS; ++f) {
                    while (inventory[f] < maxStock && shipment[f] > 0) {
                        ++inventory[f];
                        --shipment[f];
                        --bottlesRemaining;
                    }
                    
                    if (inventory[f] != maxStock) {
                        unfilledVendingMachine += maxStock - inventory[f];
                    }
                }
                
                if (unfilledVendingMachine != 0) {
                    print('U', machine.getId(), unfilledVendingMachine);
                }

                machine.restocked();
                print('D', machine.getId(), bottlesRemaining);
            }
            
        }
    }        
}

#undef print
