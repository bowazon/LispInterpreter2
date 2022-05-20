#include "Reserved.h"
#include "../Level2Parser/Level2Parser.h"

map<string, ReservedProc> ProcedureMap = {
        {"+", procPlus},
};

LispValue* procPlus(LispValue* args, LispValue* (*eval) (list<Level2Token*>)) {
    list<Level2Token*> sublists = args->get_list();
    list<Level2Token*>::iterator it;
    NumberVal* sum = new NumberVal(0);
    for(it = sublists.begin(); it != sublists.end(); ++it) {
        sum->add(dynamic_cast<NumberVal*>(eval(list<Level2Token*>(1, *it))));
    }
    return sum;
}
