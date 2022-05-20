#include <iostream>
#include "Reserved.h"
#include "Defined.h"

Defined DefinedStore; // TODO 1) not in it's place. 2) should be frames

LispValue* ProcPlus(LispValue* args, LispValue* (*eval) (list<Level2Token*>));
LispValue* ProcDefine(LispValue* args, LispValue* (*eval) (list<Level2Token*>));

map<string, ReservedProc> ProcedureMap = {
        {"+", ProcPlus},

        {"define", ProcPlus},
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

LispValue* procDefine(LispValue* args, LispValue* (*eval) (list<Level2Token*>)) {
    list<Level2Token*> sublists = args->get_list();
    // "(define a 2)" -> args - kLazy
    string name = dynamic_cast<LazyVal*>(args)->get_list().front()->get_identif_val();
    Level2Token* v = *next(dynamic_cast<LazyVal*>(args)->get_list().begin());
    LazyVal* to_name = new LazyVal(list<Level2Token*>(1, v));

    DefinedStore.Define(name, to_name);

    return new MsgToTheWorld("defined");
}
