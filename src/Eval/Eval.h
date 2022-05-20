#ifndef LISPINTERPRETER2_EVAL_H
#define LISPINTERPRETER2_EVAL_H

#include "LispValue.h"
#include "../Level2Parser/Level2Token.h"

namespace Eval {
    void InterpreterCall(string expression); // TODO temporary
    LispValue* eval(list<Level2Token*> to_eval);
}

#endif //LISPINTERPRETER2_EVAL_H
