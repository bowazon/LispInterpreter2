#include "src/Eval/Eval.h"

using namespace std;
using namespace Eval;

int main()
{
    Eval::InterpreterCall("(+ 2 3 (+ 4 7))");

    return 0;
}
