#include <iostream>
#include "playingCard.hpp"
#include "termio.h"

//using namespace std;
using namespace Term;

int main()
{
    Card c(0);
    string test = "&60Test";
    string test2 = "LOL";
    
    cout << "\n\n\n" << c << "\n\n";
    cout << test;
    cout << test2 << std::endl;
    cout << fuse(test,test2);
}