#include "playingCard.hpp"
#include "TrIO.hpp"
#include <time.h>
#include <stdlib.h>  


/*
  ██████╗ █████╗ ██████╗ ██████╗  ██████╗ ██████╗ ███╗   ██╗████████╗ █████╗ ██╗███╗   ██╗███████╗██████╗
 ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██║████╗  ██║██╔════╝██╔══██╗
 ██║     ███████║██████╔╝██║  ██║██║     ██║   ██║██╔██╗ ██║   ██║   ███████║██║██╔██╗ ██║█████╗  ██████╔╝
 ██║     ██╔══██║██╔══██╗██║  ██║██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██║██║██║╚██╗██║██╔══╝  ██╔══██╗
 ╚██████╗██║  ██║██║  ██║██████╔╝╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║██║██║ ╚████║███████╗██║  ██║
  ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝
*/

class CardContainer {
protected:
    Term::IO io;
    vector<Card *> Cards;
    int RandomIndex();
    struct CardCompare {
        bool operator()(Card *l, Card *r) {
            return *l < *r;
        }
    };

public:
    CardContainer();
    CardContainer(int);
    CardContainer(Card*);
    void Add(Card *);
    bool isEmpty();
    void Order();
    Card *Remove();
    void Reset();
    void Shuffle();
    string fuze();
    int Size();
};

CardContainer::CardContainer() {

}

    /**
     * Public : CardContainer
     *
     * Description:
     *      holds a generic vector of cards, meant to be inherited
     *
     * Params:
     *      int :  number of cards to initialize.
     *
     * Returns:
     *      None
     */
CardContainer::CardContainer(int numCards) {
    for (int i = 0; i < numCards; i++) {
        Cards.push_back(new Card(i));
    }
}
    /**
     * Public : CardContainer
     *
     * Description:
     *      holds a generic vector of cards, meant to be inherited
     *
     * Params:
     *      card* - card to be placed in the vector.
     *
     * Returns:
     *      None
     */
CardContainer::CardContainer(Card* temp){
  Cards.push_back(temp);
}

    /**
     * Public : Add
     *
     * Description:
     *      inserts a card to the end of the vector.
     *
     * Params:
     *      card - card to be placed in the vector.
     *
     * Returns:
     *      None
     */
void CardContainer::Add(Card *card) {
  Card* temp = new Card(card->getValue());

   if(card->getValue() < 52){
      Cards.push_back(temp);
    }

}

    /**
     * Public : isEmpty
     *
     * Description:
     *      determines if the vector is empty
     *
     * Params:
     *      None
     *
     * Returns:
     *      Bool - true if empty false if not
     */
bool CardContainer::isEmpty() {
    return Cards.empty();
}

    /**
     * Public : Order
     *
     * Description:
     *      sorts the vector of cards
     *
     * Params:
     *      None
     *
     * Returns:
     *      None
     */
void CardContainer::Order() {
    sort(Cards.begin(), Cards.end(), CardCompare());
}

    /**
     * Public : Remove
     *
     * Description:
     *      removes a card off the vector
     *
     * Params:
     *      None
     *
     * Returns:
     *      Card - card off of the vector.
     */
Card *CardContainer::Remove() {
    Card *temp = Cards.back();
    Cards.pop_back();
    return temp;
}

    /**
     * Public : Reset
     *
     * Description:
     *      Resets the vector and deletes everything in it.
     *
     * Params:
     *      None
     *
     * Returns:
     *      None
     */
void CardContainer::Reset() {
    for (int i = 0; i < Cards.size() - 1; i++) {
        delete Cards[i];
        Cards[i] = new Card(i);
    }
}

    /**
     * Public : Shuffle
     *
     * Description:
     *      mixes the vector
     *
     * Params:
     *      None
     *
     * Returns:
     *      None
     */
void CardContainer::Shuffle() {
  srand (time(NULL));
    for (int i = 0; i < Cards.size() - 1; i++) {
        int j = i + rand() % (Cards.size() - i);
        swap(Cards[i], Cards[j]);
    }
}

    /**
     * Public : Size
     *
     * Description:
     *      returns the size of the vector
     *
     * Params:
     *      None
     *
     * Returns:
     *      int - size of the vector
     */
int CardContainer::Size() {
    return Cards.size();
}

    /**
     * Public : fuze
     *
     * Description:
     *      puts the vector of cards in a single string to be printed on a single line
     *
     * Params:
     *      None
     *
     * Returns:
     *      string - all cards in vector on a single line
     */
string CardContainer::fuze(){
  string temp = "";
  for(int i = 0;i < Cards.size(); i++){
    temp = trio::fuse(temp, Cards[i]->Repr());
  }
  return temp;
}
