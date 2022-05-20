#ifndef LISPINTERPRETER2_DEFINED_H
#define LISPINTERPRETER2_DEFINED_H

#include <map>
#include <string>
#include "LispValue.h"

using namespace std;

class Defined {
private:
    map<string, LispValue*> defined_map;
public:
    void Define(string name, LispValue* value) {
        defined_map.insert({name, value});
    }
    LispValue* FindDefinition(string name) {
        return (defined_map.find(name))->second;
    }
    bool Contains(string name) {
        return defined_map.find(name) != defined_map.end();
    }
};

extern Defined DefinedStore;

#endif //LISPINTERPRETER2_DEFINED_H
