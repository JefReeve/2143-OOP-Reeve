#include <iostream>
#include "Game.hpp"

using namespace std;

int main()
{
  
  Term::IO io;

  Game war;

// counter i to keep track of how many turns are played.
// w is a flag to determine if there is a winner.
  int i = 0, w = 0;
  // do while since there can't be a winner before the first turn.
  do{
    cout << " *P1*   *P2*";
    // Play() returns a 0 for no winner, 1 for player 1 wins, and 2 for player 2 wins
    w = war.Play();
    cout << "\nPlayer 1 sas " << war.getCount1() << " cards.\nPlayer 2 has " << war.getCount2() << " cards.\n"
       << "*******************************************\n";
    i++;
  }while(w == 0);

  cout << "\n\nPlayer " << w << " won in " << i << " turns!";
  return 0;
}
