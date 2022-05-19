#include <iostream>
#include "Level1Parser.h"

using namespace std;
using namespace Level1Parser;

#include <string>

int main()
{
    try {
        Print(Parse("foo"));
        Print(Parse(" ( foo 3 (* 5 6) )   "));
        Print(Parse(" ( foo 3 (* 5 6) ))) (* 3 5)  "));
    } catch (WrongAmountOfBraces &w) {
        cout << "..." << endl;
        cout << w.get_msg() << endl;
    }
    return 0;
}
