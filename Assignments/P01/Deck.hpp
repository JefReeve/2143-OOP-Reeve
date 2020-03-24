#include "CardContainer.hpp"
#include "TrIO.hpp"

/*
 ██████╗ ███████╗ ██████╗██╗  ██╗
 ██╔══██╗██╔════╝██╔════╝██║ ██╔╝
 ██║  ██║█████╗  ██║     █████╔╝
 ██║  ██║██╔══╝  ██║     ██╔═██╗
 ██████╔╝███████╗╚██████╗██║  ██╗
 ╚═════╝ ╚══════╝ ╚═════╝╚═╝  ╚═╝
*/

class Deck : public CardContainer {
protected:
    int deckSize;

public:
    Deck();
    Deck(int);
    Card *Draw();
    void Print();
};

Deck::Deck() : CardContainer() {

}

    /**
     * Public : Deck
     *
     * Description:
     *      Represents a deck of cards extending CardContainer
     *
     * Params:
     *      int :  number of cards to initializes.
     *
     * Returns:
     *      None
     */
Deck::Deck(int size) : CardContainer(size) {
    deckSize = size;
}

    /**
     * Public : Draw
     *
     * Description:
     *      returns a card out of the deck and removes it from the deck.
     *
     * Params:
     *      None
     *
     * Returns:
     *      Card - card drawn from deck
     */
Card *Deck::Draw() {
    Card *temp = Cards.back();
    Cards.pop_back();
    return temp;
}

    /**
     * Public : Print
     *
     * Description:
     *      Prints out deck for testing purposes
     *
     * Params:
     *     None
     *
     * Returns:
     *      None
     */
void Deck::Print() {
    int i = 0;
    vector<string> cards;

    // if (clear) {
    //     io << Term::clear;
    // }

    for (auto c : Cards) {
        cards.push_back(c->Repr());


            io << Term::fuse(cards) << "\n";
            cards.clear();
        
    }

    // any cards left in the vector should be
    // printed out.
    if (cards.size() > 0) {
        io << Term::fuse(cards) << "\n";
    }
}
