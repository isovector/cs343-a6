#include "watcard.office.h"
#include "bank.h"
#include "printer.h"
#include <iostream>

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : printer(prt), jobList(), courierList(), numCouriers(numCouriers)
{
    for( unsigned int i = 0; i < numCouriers; i++ )
    {
        WATCardOffice::Courier *temp = new WATCardOffice::Courier( prt, bank, *this );
        courierList.push_back( temp );
    }
}

/*
* Create a watcard and a new transfer job for the amount specified and return a future watcard pointer to the card after the transfer completes
*/
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount )
{
    WATCard *newWATCard = new WATCard();
    WATCardOffice::Job *newJob = new WATCardOffice::Job( WATCardOffice::Job::JobArgList(sid,amount,newWATCard));
    jobList.push_back( newJob );
    printer.print( Printer::WATCardOffice, sid, 'C', sid, amount );
    return newJob->result;
}

/*
* Create a transfer job and return a future watcard pointer to the card after the transfer completes
*/
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card )
{
    WATCardOffice::Job *newJob = new WATCardOffice::Job( WATCardOffice::Job::JobArgList(sid,amount,card));
    jobList.push_back( newJob );
    printer.print( Printer::WATCardOffice, sid, 'T', sid, amount );
    return newJob->result;
}

/*
* Return a job that needs to be completed by a courier
*/
WATCardOffice::Job *WATCardOffice::requestWork()
{
/*
            _Accept( create, transfer ) break;
            or _Accept( ~WATCardOffice )
            {
                std::cout << "HELLO" << std::endl;
                return NULL;
            }
*/
            //return NULL;
    if( jobList.size() == 0 ) return NULL;
    WATCardOffice::Job *nextJob = jobList.front();
    jobList.pop_front();
    printer.print( Printer::WATCardOffice, 'W' );
    return nextJob;
}

WATCardOffice::~WATCardOffice()
{
    printer.print( Printer::WATCardOffice, 'F' );
    for( unsigned int i = 0; i < numCouriers; i++ )
    {
        Courier *temp = courierList.front();
        courierList.pop_front();
        delete temp;
    }
}

WATCardOffice::Courier::~Courier()
{
    
    printer.print( Printer::Courier, 'F' );
}

void WATCardOffice::main()
{
    printer.print( Printer::WATCardOffice, 'S' );

    while(true)
    {
        _Accept( ~WATCardOffice ) 
        {
            break;
        }
        or _When( jobList.size() > 0 ) _Accept( requestWork );
        or _Accept( transfer, create );
    }
    for(int i = 0; i < numCouriers; i++)
    {
        _Accept(requestWork);
    }

}

void WATCardOffice::Courier::main()
{
    printer.print(Printer::Courier, 'S');
    while(true)
    {
        _Accept(WATCardOffice::~Courier)
        {
            break;
        }
        _Else
        {
            WATCardOffice::Job *job;
            job = office.requestWork();
            if(job == NULL)
            {
                break;
            }

            printer.print(Printer::Courier, job->args.id, 't', job->args.amount);
            bank.withdraw(job->args.id, job->args.amount);
            job->args.card->deposit(job->args.amount);
            printer.print(Printer::Courier, job->args.id, 'T', job->args.amount);
            if(mprand(5) != 0)
            {
                job->result.delivery(job->args.card);
            }
            else {
                delete job->args.card;
                job->result.exception(new WATCardOffice::Lost());
                delete job;
            }
        }
    }
}

