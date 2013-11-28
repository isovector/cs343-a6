#ifndef __VENDING_MACHINE_H
#define __VENDING_MACHINE_H

_Task VendingMachine {
    void main();
  public:
    enum Flavours { ... };                 // flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maVENDING_MACHINEStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _NomuteVENDING_MACHINE unsigned int cost();
    _NomuteVENDING_MACHINE unsigned int getId();
};

#endif
