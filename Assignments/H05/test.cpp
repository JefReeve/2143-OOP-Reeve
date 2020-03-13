#include <iostream>
#include "playingCard.hpp"
#include "TrIO.hpp"

using namespace std;
//using namespace Term;

int main()
{
  
  Term::IO io;

    Card c(0);
    Card d(0);

    std::string card1 = "";
    card1 += "&28┌──┐\n";
    card1 += "&28│D9│\n";
    card1 += "&28└──┘\n";


    d.setBackgroundColor("Cyan");
    d.setForegroundColor("Green");
    d.setSuitColor("Yellow");
    d.setRankColor("Magenta");
    
    io << "\n" << c << "\n\n";
    io << "\n" << d << "\n\n";

    io << trio::fuse(c.Repr(),d.Repr()) << "\n\n";

    io << card1;
}
