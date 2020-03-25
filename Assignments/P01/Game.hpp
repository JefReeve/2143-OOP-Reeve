#include "Deck.hpp"


class Game{
private:
Deck player1;
Deck player2;

int count1;
int count2;

Term::IO io;

public:

Game();
int Play();
int War(Card* temp1, Card* temp2);
// void Print1();
// void Print2();
int getCount1();
int getCount2();
};

    /**
     * Public : Deck
     *
     * Description:
     *      Represents the main functions of the game.
     *        Consstructor initializes a deck of 52 cards and shuffles it
     *        before splitting it between the two players.
     *
     * Params:
     *      None
     *
     * Returns:
     *      None
     */
Game::Game(){
  Deck temp(52);
  temp.Shuffle();
      for(int i = 0; i < 26; i++){
      player1.Add(temp.Draw());
      player2.Add(temp.Draw());
    }
    count1 = 26;
    count2 = 26;
}

    /**
     * Public : Play
     *
     * Description:
     *      Represents the main proccess of each round
     *
     * Params:
     *      None
     *
     * Returns:
     *      int - 0 if no winner, 1 if player 1 wins, 2 if player 2 wins
     */
int Game::Play(){
  // temp cards to print and compare for round winner
  Card* temp1 = player1.Draw();
  Card* temp2 = player2.Draw();
  count1 -= 1;
  count2 -= 1;
  //prints the cards on the same line
  io << "\n" << trio::fuse(temp1->Repr(), temp2->Repr());
  //uses overloaded operators to compare their rank
  if(*temp1 > *temp2){
    player1.Add(temp1);
    player1.Add(temp2);
    //shuffles since draw and pop are from the same side of the deck
    player1.Shuffle();
    count1 += 2;
    //prints winner on the left to correspond with where the card was printed
    io << "Winner\n";
  }
  else if(*temp2 > *temp1){
    player2.Add(temp1);
    player2.Add(temp2);
    //shuffles since draw and pop are from the same side of the deck
    player2.Shuffle();
    count2 += 2;
    //prints winner to the right to correspond with where the card was printed
    io << "       Winner\n";
  }
  else{
    //if there is a tie on either players last card that player loses
    if(count1 <= 0){
      count2 += 2;
      return 2;
    }
    if(count2 <= 0){
      count1 += 2;
      return 1;
    }

    //calls war function and checks who wins it, multi wars are handled recursively
    //counts are updated by two here for the two cards being compared, rest added in the function
    if(War(temp1, temp2) == 1)
      count1 += 2;
    else
      count2 += 2;
  }

  //checks for a winner and returns corresponding number
  if(count1 <= 0)
    return 2;
  if(count2 <= 0)
    return 1;

    return 0;
}

    /**
     * Public : War
     *
     * Description:
     *      if players draw cards of equal value each draws 4 cards and
     *      compares the 4th card winner gets all 8.
     *
     * Params:
     *      Card* - player 1s card
     *      Card* - player 2s card
     *
     * Returns:
     *      int - 0 if no winner, 1 if player 1 wins, 2 if player 2 wins
     */
int Game::War(Card* temp1, Card* temp2){
    //arrays of 5 size to hold the original cards that caused the war
    Card* arr1[5];
    Card* arr2[5];
    arr1[0] = temp1;
    arr2[0] = temp2;
    //string of upside cards for each player
    string hideCards1 = "";
    string hideCards2 = "";
    //amount of cards each player is betting(will be 4 unless they dont have enough)
    int bet1 = 0;
    int bet2 = 0;
    Card* compare1;
    Card* compare2;
    int recur = 0;

// if a player doesnt have enough cards to play the full war
    if(count1 < 4){
      for(int i = 1; i <= count1; i++){
        arr1[i] = player1.Draw();
        //shows adds an upside down card to the string for each drawn
        //if to show one less upside down card for the card being compared
        if(bet1 != 0)
          hideCards1 = trio::fuse(hideCards1, arr1[i]->faceDown());
        bet1++;
      }
      count1 = 0;
      bet2 = 4;
      //adds the cards and facedown cards for the winning player
        for(int i = 1; i < 4; i++){
          arr2[i] = player2.Draw();
          hideCards2 = trio::fuse(hideCards2, arr2[i]->faceDown());
          count2--;
        }
          //draws the card to compare
          arr2[4] = player2.Draw();
          hideCards1 = trio::fuse(hideCards1, arr1[bet1]->Repr());
          hideCards2 = trio::fuse(hideCards2, arr2[4]->Repr());
          count2--;
          compare2 = arr2[4];
          compare1 = arr1[bet1];
    }
    else if(count2 < 4){
      for(int i = 1; i <= count2; i++){
        arr2[i] = player2.Draw();
        //shows adds an upside down card to the string for each drawn
        //if to show one less upside down card for the card being compared
        if(bet2 != 0)
          hideCards2 = trio::fuse(hideCards2, arr2[i]->faceDown());
        bet2++;
      }
      count2 = 0;
      bet1 = 4;
      //adds the cards and facedown cards for the winning player
        for(int i = 1; i < 4; i++){
          arr1[i] = player1.Draw();
          hideCards1 = trio::fuse(hideCards1, arr1[i]->faceDown());
          count1--;
        }
        //draws the cards to compare
          arr1[4] = player1.Draw();
          hideCards1 = trio::fuse(hideCards1, arr1[4]->Repr());
          hideCards2 = trio::fuse(hideCards2, arr2[bet2]->Repr());
          count1--;
          compare1 = arr1[4];
          compare2 = arr2[bet2];
    }
    else{
      //draws 3 cards and adds the facedown cards
        for(int i = 1; i < 4; i++){
          arr1[i] = player1.Draw();
          arr2[i] = player2.Draw();
          hideCards1 = trio::fuse(hideCards1, arr1[i]->faceDown());
          hideCards2 = trio::fuse(hideCards2, arr2[i]->faceDown());
          count1--;
          count2--;
        }
        //draws the cards to be compared
          arr1[4] = player1.Draw();
          arr2[4] = player2.Draw();
          compare1 = arr1[4];
          compare2 = arr2[4];
          hideCards1 = trio::fuse(hideCards1, compare1->Repr());
          hideCards2 = trio::fuse(hideCards2, compare2->Repr());
          count1--;
          count2--;
          bet2 = 4;
          bet1 = 4;
    }
    io << "\n__        ___    ____\n"; 
    io << "\\ \\      / / \\  |  _ \\ \n";
    io << " \\ \\ /\\ / / _ \\ | |_) |\n";
    io << "  \\ V  V / ___ \\|  _ < \n";
    io << "   \\_/\\_/_/   \\_\\_| \\_\\\n";

    io << "\n" << trio::fuse(hideCards1, "\n-Player 1s hand");
    io << "\n" << trio::fuse(hideCards2, "\n-Player 2s hand") << "\n";

  if(*compare1 > *compare2){
    //adds both players cards to the winners deck
      for(int i = 0; i < bet1 + 1; i++){
        player1.Add(arr1[i]);
      }
      for(int i = 0; i < bet2 + 1; i++){
        player1.Add(arr2[i]);
      }
    player1.Shuffle();
    count1 += (bet1 + bet2);
    
    io << "Player 1 wins the war!\n";
    return 1;
  }
  else if(*compare2 > *compare1){
    //adds both players cards to the winners deck
      for(int i = 0; i < bet1 + 1; i++){
        player2.Add(arr1[i]);
      }
      for(int i = 0; i < bet2 + 1; i++){
        player2.Add(arr2[i]);
      }
    player2.Shuffle();
    count2 += (bet1 + bet2);

    io << "Player 2 wins the war!\n";
    return 2;
  }
  else{
    //recursive call if there is a war in the war
    //recur variable to dermin who won the war(s)
    recur = War(compare1,compare2);
    if(recur == 1){
      for(int i = 0; i < bet1; i++){
        player1.Add(arr1[i]);
      }
      for(int i = 0; i < bet2; i++){
        player1.Add(arr2[i]);
      }
    player1.Shuffle();
    count1 += (bet1 + bet2);
    }
    else if(recur == 2){
      for(int i = 0; i < bet1; i++){
        player2.Add(arr1[i]);
      }
      for(int i = 0; i < bet2; i++){
        player2.Add(arr2[i]);
      }
    player2.Shuffle();
    count2 += (bet1 + bet2);
    }
    return recur;
  }
}

    /**
     * Public : getCount1
     *
     * Description:
     *      gets the deck size for player 1.
     *
     * Params:
     *      None
     *
     * Returns:
     *      int - deck size for player 1
     */
int Game::getCount1(){
  return count1;
}

    /**
     * Public : getCount2
     *
     * Description:
     *      gets the deck size for player 2.
     *
     * Params:
     *      None
     *
     * Returns:
     *      int - deck size for player 2
     */
int Game::getCount2(){
  return count2;
}

//print methods for testing
// void Game::Print1(){
//   player1.Print();
// }

// void Game::Print2(){
//   player2.Print();
// }
