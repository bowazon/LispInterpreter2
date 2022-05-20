#include "Eval.h"
#include "../Level1Parser/Level1Parser.h"
#include "../Level2Parser/Level2Parser.h"
#include "../Helper.h"
#include "Reserved.h"
#include <iostream>

//using namespace std;

namespace Eval {

void InterpreterCall(string expression) {
    list<Level2Token*> to_eval = Level2Parser::Parse(Level1Parser::Parse(expression));
    cout << ">>>" << expression << endl;
    cout << "..." << eval(to_eval)->to_string() << endl;
}

/*
enum class LispValueType {
    kNumber,
    kBoolean,
    kQuot,
    kIdentifier,
    kBuiltIn,
    kLazy,
    kError
};
 */

bool IsBuiltInFunction(string s);
list<Level2Token*> rest(list<Level2Token*> my_list);

LispValue* apply(LispValue* operat, LispValue* operands);

LispValue* eval(list<Level2Token*> to_eval) {
    if (to_eval.size() == 1) {
        Level2Token* crnt = to_eval.front();
        if (crnt->get_type() == Level2TokenType::kIdentifier) {
            string s = crnt->get_identif_val();
            if (Helper::IsNumber(s)) return new NumberVal(s); // TODO if they all gonna be (s),
            if (Helper::IsBoolean(s)) return new BooleanVal(s); // maybe I need a factory??
            if (IsBuiltInFunction(s)) return new BuiltIn(ProcedureMap.find(s)->second);
            //if ()
        } else {
            // TODO if we eval("(+ 2 3 (+ 4 7))") then lazy "(+ 4 7)" traps here
            return eval(Level2Parser::Parse(to_eval.front()->get_unparsed_list())); // TODO bad
            // I don't want to call
        }
    } else {
        LispValue* operat = eval(list<Level2Token*>(1, to_eval.front()));
        return apply(operat, new LazyVal(rest(to_eval)));
        //return apply(eval(to_eval.front()), to_eval); // TODO level2 Tokens or LispValues???
    }

    return new ErrorVal("Some eval() error");
}

LispValue* apply(LispValue* operat, LispValue* operands) {
    if(operat->get_type() == LispValueType::kBuiltIn) {
        return dynamic_cast<BuiltIn*>(operat)->get_proc()(operands, eval);
    }

    return new ErrorVal("Some apply() error");
}

list<Level2Token*> rest(list<Level2Token*> my_list) { // TODO how da fuck get sublist from second to end???
    list<Level2Token*>::iterator it;
    list<Level2Token*> retval;
    for(it = next(my_list.begin()); it != my_list.end(); ++it) {
        retval.push_back(*it);
    }
    return retval;
}

bool IsBuiltInFunction(string s) {
    return ProcedureMap.find(s) != ProcedureMap.end();
}

}