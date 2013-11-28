#include "nameserver.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
    printer(prt)
{
}

void NameServer::main() {
}

void NameServer::VMregister(VendingMachine *vendingmachine) {
}

VendingMachine* NameServer::getMachine(unsigned int id) {
    return NULL;
}

VendingMachine** NameServer::getMachineList() {
    return NULL;
}
