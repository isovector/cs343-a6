#include "watcard.office.h"
#include "bank.h"
#include "printer.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : 
    printer(prt), numCouriers(numCouriers)
{
    for( unsigned int i = 0; i < numCouriers; i++ ) {
        // create couriers
        courierList.push_back(new WATCardOffice::Courier( prt, bank, *this ));
    }
}

/*
* Create a watcard and a new transfer job for the amount specified and return a future watcard pointer to the card after the transfer completes
*/
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    WATCard *newWATCard = new WATCard();
    WATCardOffice::Job *newJob = new WATCardOffice::Job( WATCardOffice::Job::JobArgList(sid,amount,newWATCard));
    jobList.push_back( newJob );
    
    printer.print( Printer::WATCardOffice, sid, 'C', sid, amount );
    return newJob->result;
}

/*
* Create a transfer job and return a future watcard pointer to the card after the transfer completes
*/
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    WATCardOffice::Job *newJob = new WATCardOffice::Job( WATCardOffice::Job::JobArgList(sid,amount,card));
    jobList.push_back( newJob );
    
    printer.print( Printer::WATCardOffice, sid, 'T', sid, amount );
    return newJob->result;
}

/*
* Return a job that needs to be completed by a courier
*/
WATCardOffice::Job *WATCardOffice::requestWork() {
    if( jobList.size() == 0 ) {
        return NULL;
    }
    
    WATCardOffice::Job *nextJob = jobList.front();
    jobList.pop_front();
    
    printer.print( Printer::WATCardOffice, 'W' );
    return nextJob;
}

WATCardOffice::~WATCardOffice() {
    printer.print( Printer::WATCardOffice, 'F' );
    
    // get rid of the couriers
    while (!courierList.empty()) {
        delete courierList.front();
        courierList.pop_front();
    }
    
    // clean up jobs
    while(!jobList.empty()) {
        delete jobList.front();
        jobList.pop_front();
    }
}

WATCardOffice::Courier::~Courier() {
    printer.print( Printer::Courier, 'F' );
}

void WATCardOffice::main() {
    printer.print( Printer::WATCardOffice, 'S' );

    while(true) {
        _Accept( ~WATCardOffice ) {
            break;
        }
        or _When( jobList.size() > 0 ) _Accept( requestWork );
        or _Accept( transfer, create );
    }
    
    // unblock couriers
    for(size_t i = 0; i < numCouriers; i++) {
        _Accept(requestWork);
    }
}

void WATCardOffice::Courier::main() {
    printer.print(Printer::Courier, 'S');
    
    while(true) {
        _Accept(WATCardOffice::~Courier) {
            // peace out, infinite loop
            break;
        } _Else {
            WATCardOffice::Job *job;
            job = office.requestWork();
            
            if(job == NULL) {
                break;
            }

            printer.print(Printer::Courier, job->args.id, 't', job->args.amount);
            bank.withdraw(job->args.id, job->args.amount);
            job->args.card->deposit(job->args.amount);
            printer.print(Printer::Courier, job->args.id, 'T', job->args.amount);
            
            if(mprand(5) != 0) {
                // don't lose the card
                job->result.delivery(job->args.card);
            } else {
                // lose the card!
                delete job->args.card;
                job->result.exception(new WATCardOffice::Lost());
            }
            
            delete job;
        }
    }
}

