#ifndef LISPINTERPRETER2_RESERVED_H
#define LISPINTERPRETER2_RESERVED_H

#include "LispValue.h"
#include <map>


extern map<string, ReservedProc> ProcedureMap;


//typedef LispValue* (*ReservedProc) (list<LispValue*> args, LispValue* (*eval) (list<Level2Token*>));

#endif //LISPINTERPRETER2_RESERVED_H
