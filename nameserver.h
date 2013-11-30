#ifndef __NAME_SERVER_H
#define __NAME_SERVER_H

#include "printer.h"
_Task NameServer;
#include "vendingmachine.h"

#include <vector>

_Task NameServer {
    Printer &printer;
    std::vector<VendingMachine*> machines;
    
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
