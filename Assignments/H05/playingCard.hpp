#include "termio.h"
#include <algorithm> // std::random_shuffle
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace Term;

const string spade = "♠";
const string diamond = "♦";
const string heart = "♥";
const string club = "♣";

const string suits[4] = {"♠", "♦", "♣", "♥"};

// Black background        blue ,  red , blue , red
const string colors2[4] = {"&60", "&20", "&60", "&20"};

// Colored background      blue  , red  , blue , red
const string colors[4] = {"&16", "&12", "&16", "&12"};

// Card labels (could be "Iron Man" or "Charmander" or "Elf" ... anything)
const string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};


/*
  ██████╗ █████╗ ██████╗ ██████╗
 ██╔════╝██╔══██╗██╔══██╗██╔══██╗
 ██║     ███████║██████╔╝██║  ██║
 ██║     ██╔══██║██╔══██╗██║  ██║
 ╚██████╗██║  ██║██║  ██║██████╔╝
  ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝
*/

class Card {
private:
    int suitNum;     // value 0-3 : num index of suit
    int rank;        // 0-13      : num value of rank
    int number;      // 1-52      : unique value determines card
    int value;       // 1-14      : numeric value used for comparison
    string suitChar; // "♠", "♦", "♣", "♥"
    string rankChar; // Ace, 1 ,2 ,3 ... Q, K
    string color;    // Spade=blue, Diamond=red, etc.
    string foreColor;// edges of cards and default otherwise
    string backColor;// Defaults to white
    string suitColor;// color of suit, defaults to color
    string rankColor;// color of number/rank, defaults to color

public:
    friend ostream;

    Card(int);
    string Repr();
    bool operator<(const Card &);
    bool operator>(const Card &);
    bool operator==(const Card &);
    bool operator!=(const Card &);
    bool operator()(const Card &);
    void setForegroundColor(string newColor);       // set foreground color of card
    void setBackgroundColor(string newColor);      // set background color of card
    void setColors(string fore,string back);      // set fore and back
    void setSuitColor(string newColor);        // set symbol color 
    void setRankColor(string newColor);          // set number color
    void setColors(string fore, string back, string symbol, string number);
    string getColor(string text);
    // and any other overloaded convenience methods you want to add. 

};
/**
     * Public : Card
     *
     * Description:
     *      Represents a single card in a deck of cards to include a
     *      value along with rank and suit. We are assuming a standard
     *      card type in a deck of playing cards.
     *
     * Params:
     *      int :  value from 0 - 51 that represents a card in a deck.
     *
     * Returns:
     *      None
     */
Card::Card(int num) {
    number = num;
    suitNum = number / 13;
    suitChar = suits[suitNum];
    color = colors[suitNum];
    rank = number % 13;
    rankChar = ranks[rank];
    if(suitNum % 2 == 0)
      foreColor = "5";
    else
      foreColor = "2";

    backColor = "8";
    suitColor = color;
    rankColor = color;
}

/**
     * Public : Repr
     *
     * Description:
     *      Returns a string representation of the card class with
     *      colors embedded.
     *
     * Params:
     *      None
     *
     * Returns:
     *      [string] - representation of card
     */
string Card::Repr() {
    string s = "";
    s += color + "┌────┐&00 \n";
    s += color + "│";
    // if (rank != 9) {
    //     s += color + " ";
    // }
    s += rankColor + rankChar + " " + suitColor + suitChar + "│&00 \n";
    s += color + "└────┘&00 ";
    return s;
}

/**
 * Public : operator <<
 *
 * Description:
 *      Overload ostream and send the string representation "Repr"
 *      of the card.
 *
 *      We don't need the scope resolution operator (Card::) since
 *      this is a "friend" of card.
 *
 * Params:
 *      [ostream&] : os
 *      [Card]     : obj
 *
 * Returns:
 *      [ostream&]
 */
ostream &operator<<(ostream &os, Card obj) {

    os << obj.Repr();

    return os;
}

bool Card::operator<(const Card &rhs) {
    return this->rank < rhs.rank;
}

bool Card::operator>(const Card &rhs) {
    return this->rank > rhs.rank;
}

bool Card::operator==(const Card &rhs) {
    return this->rank == rhs.rank;
}

bool Card::operator!=(const Card &rhs) {
    return this->rank != rhs.rank;
}

bool Card::operator()(const Card &rhs) {
    return (this->rank < rhs.rank);
}

string Card::getColor(string text){
    string temp = "";

    if(text == "Black")
      temp = "1";
    else if(text == "Red")
      temp = "2";
    else if(text == "Yellow")
      temp = "3";
    else if(text == "Green")
      temp = "4";
    else if(text == "Blue")
      temp = "5";
    else if(text == "Cyan")
      temp = "6";
    else if(text == "Magenta")
      temp = "7";
    else if(text == "White")
      temp = "8";
    else
      temp = "0";
    
    return temp;
}

void Card::setForegroundColor(string newColor){
    foreColor = getColor(newColor);
    color = "&" + backColor + foreColor;
}

void Card::setBackgroundColor(string newColor){
    backColor = getColor(newColor);
    color = "&" + backColor + foreColor;
    suitColor = "&" + backColor + foreColor;
    rankColor = "&" + backColor + foreColor;
}

void Card::setColors(string fore,string back){
    foreColor = fore;
    backColor = back;
    color = "&" + getColor(backColor) + getColor(foreColor);
    
}

void Card::setSuitColor(string newColor){
    suitColor = "&" + backColor + getColor(newColor);
}

void Card::setRankColor(string newColor){
    rankColor = "&" + backColor + getColor(newColor);
}

void Card::setColors(string fore, string back, string symbol, string number){
    foreColor = fore;
    backColor = back;
    suitColor = symbol;
    rankColor = number;
    color = "&" + backColor + foreColor;
}
