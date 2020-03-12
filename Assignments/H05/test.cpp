#include <iostream>
#include "playingCard.hpp"
#include "termio.h"

//using namespace std;
using namespace Term;

int main()
{
    Card c(0);
    Card d(0);

    d.setBackgroundColor("Magenta");
    d.setForegroundColor("Yellow");
    d.setSuitColor("Blue");
    d.setRankColor("Cyan");
    
    cout << "\n" << c << "\n\n";
    cout << "\n" << d << "\n\n";
}
