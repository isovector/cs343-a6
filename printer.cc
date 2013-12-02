#include "printer.h"
#include <iostream>
#include <sstream>
using namespace std;

Printer::StateNum::StateNum(char state) :
    state(state), nums(0), num1(0), num2(0)
{ }

Printer::StateNum::StateNum(char state, int num1) :
    state(state), nums(1), num1(num1), num2(0)
{ }

Printer::StateNum::StateNum(char state, int num1, int num2) :
    state(state), nums(2), num1(num1), num2(num2)
{ }

bool Printer::StateNum::operator==(char other) {
    return state == other;
}

bool Printer::StateNum::operator!=(char other) {
    return !operator==(other);
}

bool Printer::StateNum::operator==(const StateNum &other) {
    return state == other.state && nums == other.nums 
        && num1 == other.num1 && num2 == other.num2;
}

bool Printer::StateNum::operator!=(const StateNum &other) {
    return !operator==(other);
}

// Get a string representation of this statenum
string Printer::StateNum::getString() const {
    stringstream stream;
    
    stream << state;
    if (nums != 0) {
        stream << num1;
        
        if (nums == 2) {
            stream << "," << num2;
        }
    }
    
    return stream.str();
}

// ------------------------------------

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers) :
    numStudents(numStudents), numMachines(numVendingMachines), numCouriers(numCouriers)
{
    for (size_t i = 0; i < 5 + numStudents + numMachines + numCouriers; ++i) {
        states.push_back(StateNum(' '));
    }
    
    // print preamble
    cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";
    
    for (size_t i = 0; i < numStudents; ++i) {
        cout << "Stud" << i << "\t";
    }
    
    for (size_t i = 0; i < numMachines; ++i) {
        cout << "Mach" << i << "\t";
    }
    
    for (size_t i = 0; i < numCouriers; ++i) {
        cout << "Cour" << i << "\t";
    }
    
    cout << endl;
    for (size_t i = 0; i < states.size(); ++i) {
        cout << "******\t";
    }
    cout << endl;
}

void Printer::print(Kind kind, char state) {
    printRaw(getIndex(kind, 0), StateNum(state));
}

void Printer::print(Kind kind, char state, int value1) {
    printRaw(getIndex(kind, 0), StateNum(state, value1));
}

void Printer::print(Kind kind, char state, int value1, int value2) {
    printRaw(getIndex(kind, 0), StateNum(state, value1, value2));
}

void Printer::print(Kind kind, unsigned int lid, char state) {
    printRaw(getIndex(kind, lid), StateNum(state));
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1) {
    printRaw(getIndex(kind, lid), StateNum(state, value1));
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1, int value2) {
    printRaw(getIndex(kind, lid), StateNum(state, value1, value2));
}

void Printer::printRaw(size_t id, StateNum state) {
    if ((states[id] != state && states[id] != ' ') || state == 'F') {
        flush();
    }
    
    if (state == 'F') {
        // Write out finished lines
        for (size_t i = 0; i < states.size(); ++i) {
            cout << (id == i ? "F" : "...") << "\t";
        }
        
        cout << endl;
    } else {
        states[id] = state;
    }
}

// Output the printer buffer
void Printer::flush() {
    bool isDirty = false;
    for (vector<StateNum>::iterator it = states.begin(); it != states.end(); ++it) {
        // operator != is not defined
        if (*it != ' ') {
            isDirty = true;
            break;
        }
    }
    
    // Nothing has changed, so no need to print
    if (!isDirty) {
        return;
    }
    
    for (vector<StateNum>::iterator it = states.begin(); it != states.end(); ++it) {
        cout << it->getString() << "\t";
        
        // Set state of this element to None
        *it = StateNum(' ');
    }
    
    cout << endl;
}

size_t Printer::getIndex(Kind kind, unsigned int id) {
    switch (kind) {
        case Parent:        return 0;
        case WATCardOffice: return 1;
        case NameServer:    return 2;
        case Truck:         return 3;
        case BottlingPlant: return 4;
        
        // fall through between cases is intentional
        case Courier:       id += numMachines;
        case Vending:       id += numStudents;
        case Student:       id += 5;
        default:            return id;
    }
}
