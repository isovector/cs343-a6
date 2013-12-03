#include "student.h"
#include "watcard.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
        unsigned int maxPurchases ) :
    printer(prt), server(nameServer), office(cardOffice), id(id), toPurchase(mprand(1, maxPurchases))
{
}

#define print(state, varargs...) printer.print(Printer::Student, id, state, ##varargs)

void Student::main() {
    FWATCard fcard = office.create(id, 5);

    VendingMachine::Flavours flavor = static_cast<VendingMachine::Flavours>(mprand(VendingMachine::NUM_FLAVOURS - 1));
    
    print('S', static_cast<unsigned int>(flavor), toPurchase);
    
    VendingMachine *machine = server.getMachine(id);
    print('V', machine->getId());
    
    while (toPurchase > 0) {
        yield(mprand(1, 10));
        
        while (true) {
            try {
                WATCard *card = fcard();
                switch (machine->buy(flavor, *card)) {
                    case VendingMachine::BUY: {
                        toPurchase--;
                        print('B', card->getBalance());
                    } break;
                    
                    case VendingMachine::STOCK: {
                        machine = server.getMachine(id);
                        print('V', machine->getId());
                    } break;
                    
                    case VendingMachine::FUNDS: {
                        fcard = office.transfer(id, 5 + machine->cost(), card);
                    } break;
                }
            } catch (WATCardOffice::Lost lost) {
                print('L');
                fcard = office.create(id, 5);
                continue;
            }
            
            break;
        }
    }
    
    print('F');
}

#undef print
