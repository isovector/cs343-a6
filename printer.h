#ifndef __PRINTER_H
#define __PRINTER_H

#include <string>
#include <vector>

_Monitor Printer {
    class StateNum {
        char state;
        size_t nums;
        int num1;
        int num2;
        
      public:
        explicit StateNum(char state);
        explicit StateNum(char state, int num1);
        explicit StateNum(char state, int num1, int num2);
      
        bool operator==(char state);
        bool operator!=(char state);
        bool operator==(const StateNum &other);
        bool operator!=(const StateNum &other);
        std::string getString() const;
    };
    
    void flush();
    void printRaw(size_t id, StateNum state);

    unsigned int numStudents, numMachines, numCouriers;
    std::vector<StateNum> states;
    
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
    
  private:
    size_t getIndex(Kind kind, unsigned int lid);
};

#endif
