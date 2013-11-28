#include "watcard.office.h"
#include "bank.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : printer(prt) 
{
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount )
{
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card )
{
    WATCardOffice::Job newJob( WATCardOffice::Job::JobArgList(sid,amount,card));
    card->deposit(amount);
    
    return newJob.result;
}

WATCardOffice::Job *WATCardOffice::requestWork()
{
}

void WATCardOffice::main()
{
}

void WATCardOffice::Courier::main()
{
    
    WATCardOffice::Job *job;
    job = office.requestWork();
    bank.withdraw(job->args.id, job->args.amount);
    job->result = office.transfer( job->args.id, job->args.amount, job->args.card );

    
    
}
