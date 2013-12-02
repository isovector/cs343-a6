#include "nameserver.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
    printer(prt), numStudents(numStudents)
{
    machines.reserve(numVendingMachines);
    
    for (size_t i = 0; i < numStudents; ++i) {
        position.push_back(i % numVendingMachines);
    }
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
    ++position[id];
    position[id] %= machines.size();
    
    size_t pos = position[id];
    print('N', id, machines[pos]->getId());
    return machines[pos];
}

VendingMachine** NameServer::getMachineList() {
    return &machines[0];
}

#undef print
