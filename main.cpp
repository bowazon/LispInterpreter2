#include <iostream>
#include "Level1Parser.h"

using namespace std;
using namespace Level1Parser;

#include <string>

int main()
{
    Print(Parse("foo"));
    Print(Parse(" ( foo 3 (* 5 6)  )   "));
    return 0;
}
