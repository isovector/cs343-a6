#include "nameserver.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
    printer(prt)
{
    machines.reserve(numVendingMachines);
}

#define print(state, varargs...) printer.print(Printer::NameServer, state, ##varargs)

NameServer::~NameServer() {
    print('F');
}

void NameServer::main() {
    print('S');
    
    while (true) {
        _Accept(~NameServer) {
            break;
        } 
        or _Accept(VMregister) { }
        or _Accept(getMachine) { }
        or _Accept(getMachineList) { }
    }
}

void NameServer::VMregister(VendingMachine *vendingmachine) {
    machines.push_back(vendingmachine);
    print('R', vendingmachine->getId());
}

VendingMachine* NameServer::getMachine(unsigned int id) {
    // TODO: this is 100% wrong
    print('N', id, machines[id]->getId());
    return machines[id];
}

VendingMachine** NameServer::getMachineList() {
    return &machines[0];
}

#undef print
