#include "src/Eval/Eval.h"

using namespace std;
using namespace Eval;

int main()
{
    //Eval::InterpreterCall("(+ 2 3 (+ 4 7))");
    Eval::InterpreterCall("(define a (+ 3 5)))");
    Eval::InterpreterCall("a");

    return 0;
}
