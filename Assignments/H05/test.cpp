#include <iostream>
#include "playingCard.hpp"
#include "termio.h"

//using namespace std;
using namespace Term;

int main()
{
    Card c(50);
    Card d(0);
    string test = "&60Test\n";
    string test2 = "LOL";
    
    cout << "\n" << c << "\n\n";
    cout << "\n" << d << "\n\n";
    cout << test;
    cout << test2 << std::endl;
    cout << fuse(test,test2);
}
