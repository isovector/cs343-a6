#include "watcard.office.h"
#include "bank.h"
#include "printer.h"
#include <iostream>

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : printer(prt), jobList()
{
    for( unsigned int i = 0; i < numCouriers; i++ )
    {
        WATCardOffice::Courier *temp = new WATCardOffice::Courier( prt, bank, *this );
        courierList.push_back( temp );
    }
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount )
{
    std::cout<< "ww";
    WATCard *newWATCard = new WATCard();
    std::cout<< "cc";
    WATCardOffice::Job *newJob = new WATCardOffice::Job( WATCardOffice::Job::JobArgList(sid,amount,newWATCard));
    std::cout<< "nj";
    jobList.push_back( newJob );
    std::cout<< "pb";
    printer.print( Printer::WATCardOffice, sid, 'C', amount );
    return newJob->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card )
{
    WATCardOffice::Job *newJob = new WATCardOffice::Job( WATCardOffice::Job::JobArgList(sid,amount,card));
    jobList.push_back( newJob );
    printer.print( Printer::WATCardOffice, sid, 'T', amount );
    return newJob->result;
}

WATCardOffice::Job *WATCardOffice::requestWork()
{
    if( jobList.size() < 1 )
    {
        _Accept( create, transfer );
        //return NULL;
    }
    WATCardOffice::Job *nextJob = jobList.front();
    jobList.pop_front();
    printer.print( Printer::WATCardOffice, 'W' );
    return nextJob;
}

void WATCardOffice::main()
{
    printer.print( Printer::WATCardOffice, 'S' );

    std::cout << "l";
    while(true)
    {
        _Accept( ~WATCardOffice ) 
        {
            break;
        }
        or _Accept( transfer, create, requestWork );
    }
    std::cout << "f";
    printer.print( Printer::WATCardOffice, 'F' );
}

void WATCardOffice::Courier::main()
{
    
    printer.print( Printer::Courier, 'S' );
    std::cout << "courier started";
    while(true)
    {
        WATCardOffice::Job *job;
        job = office.requestWork();
        std::cout << "Recieved card";

        printer.print( Printer::Courier, job->args.id, 't', job->args.amount );
        bank.withdraw(job->args.id, job->args.amount);
        job->args.card->deposit(job->args.amount);
        printer.print( Printer::Courier, job->args.id, 'T', job->args.amount );
        if(mprand(5) != 0)
        {
            job->result.delivery(job->args.card);
        }
        else {
            std::cout << "delete" << std::endl;
            delete job->args.card;
            std::cout << "end delete" << std::endl;
            job->result.exception(new WATCardOffice::Lost());
        }
    }
    printer.print( Printer::Courier, 'F' );
    
}

/*
* Test Program
#include "MPRNG.h"
#include "parent.h"
MPRNG mprand;

void uMain::main()
{
    std::cout << "Start" << std::endl;
    Bank *bank = new Bank( 10 ); 
    Printer *printer = new Printer( 0, 0, 0 );
    Parent *parent = new Parent( *printer, *bank, 10, 10 );
    WATCardOffice *office = new WATCardOffice( *printer, *bank, 3 );
    WATCard *cards[10];

    std::cout << "Creating cards and putting money in the bank" << std::endl;
    for( int i = 0; i < 10; i++ )
    {
        std::cout << "\tMoney Deposited" << std::endl;
        WATCard::FWATCard card = office->create( i, 5 );
        std::cout << "\tCard created" << std::endl;
        try
        {
            cards[i] = card();
        }
        catch( WATCardOffice::Lost e )
        {
            std::cout << "\tCaught exception";
            i--;
            continue;
        }
        std::cout << "\tCard recieved" << std::endl;
        int balance = cards[i]->getBalance();
        std::cout << "BALANCE: " << balance << std::endl;
    }

    std::cout << "Transfering money from the bank" << std::endl;
    for( int i = 0; i < 10; i++ )
    {
        WATCard::FWATCard  card = office->transfer( (int)i, 5, cards[i] ); 
        try
        {
            cards[i] = card();
        }
        catch( WATCardOffice::Lost e )
        {
            std::cout << "\tCaught exception";
            continue;
        }
        int balance = cards[i]->getBalance();
        std::cout << "BALANCE: " << balance << std::endl;
    }

    
    while(true)
    {
    }
    
}
*/
