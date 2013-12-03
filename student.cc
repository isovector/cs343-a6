#include "student.h"
#include "watcard.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
        unsigned int maxPurchases ) :
    printer(prt), server(nameServer), office(cardOffice), id(id), toPurchase(mprand(1, maxPurchases))
{
}

// helper printer
#define print(state, varargs...) printer.print(Printer::Student, id, state, ##varargs)

void Student::main() {
    FWATCard fcard = office.create(id, 5);

    VendingMachine::Flavours flavor = static_cast<VendingMachine::Flavours>(mprand(VendingMachine::NUM_FLAVOURS - 1));
    
    print('S', static_cast<unsigned int>(flavor), toPurchase);
    
    VendingMachine *machine = server.getMachine(id);
    print('V', machine->getId());
    
    WATCard *card;
    while (toPurchase > 0) {
        // gee I sure am thirtsy
        yield(mprand(1, 10));
        
        // continue looping until the courier STOPS loosing my damn card
        while (true) {
            try {
                // resolve future
                card = fcard();
                
                // attempt to buy
                switch (machine->buy(flavor, *card)) {
                    case VendingMachine::BUY: {
                        // great success
                        toPurchase--;
                        print('B', card->getBalance());
                    } break;
                    
                    case VendingMachine::STOCK: {
                        // machine is out of stock, get a new machine
                        machine = server.getMachine(id);
                        print('V', machine->getId());
                    } break;
                    
                    case VendingMachine::FUNDS: {
                        // MOM I DONT HAVE ENOUGH $$$
                        fcard = office.transfer(id, 5 + machine->cost(), card);
                    } break;
                }
            } catch (WATCardOffice::Lost lost) {
                // courier lost my watcard... have to get a new one
                print('L');
                fcard = office.create(id, 5);
                continue;
            }
            
            // exit from loop
            // control flow only gets here it the try block was successful
            break;
        }
    }
    
    // no memory leaks please
    delete card;
    
    print('F');
}

#undef print
