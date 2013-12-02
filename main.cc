#include <vector>
#include <iostream>
using namespace std;

#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watcard.office.h"
#include "nameserver.h"
#include "vendingmachine.h"
#include "bottlingplant.h"
#include "student.h"

#include "MPRNG.h"
MPRNG mprand;

/*
* Usage message
*/
void usage() {
    cout << "Usage: ./soda [ config-file [ random-seed ] ]" << endl;
    exit(1);
}//end usage

void uMain::main() {
    if (argc > 3) {
        usage();
    }//end if
    
    const char *filename = argc > 1 ? argv[1] : "soda.config";
    mprand.seed(argc > 2 ?  atoi(argv[2]) : 1337);
    
    ConfigParams params;
    processConfigFile(filename, params);
    
    Printer printer(params.numStudents, params.numVendingMachines, params.numCouriers);
    Bank bank(params.numStudents);
    Parent *parent = new Parent(printer, bank, params.numStudents, params.parentalDelay);
    WATCardOffice *office = new WATCardOffice(printer, bank, params.numCouriers);
    NameServer *server = new NameServer(printer, params.numVendingMachines, params.numStudents);
    BottlingPlant *plant = new BottlingPlant(printer, *server, params.numVendingMachines, params.maxShippedPerFlavour, params.maxStockPerFlavour, params.timeBetweenShipments);
    
    vector<VendingMachine*> machines;
    for (size_t i = 0; i < params.numVendingMachines; ++i) {
        VendingMachine *machine = new VendingMachine(printer, *server, i, params.sodaCost, params.maxStockPerFlavour);
        machines.push_back(machine);
        server->VMregister(machine);
    }
    
    vector<Student*> students;
    for (size_t i = 0; i < params.numStudents; ++i) {
        students.push_back(new Student(printer, *server, *office, i, params.maxPurchases));
    }
    
    for (size_t i = 0; i < params.numStudents; ++i) {
        delete students[i];
    }

    delete plant;
    
    for (size_t i = 0; i < params.numVendingMachines; ++i) {
        delete machines[i];
    }
    delete office;
    delete server;
    delete parent;
    
    cout << "***********************" << endl;
}
