#include "card.hpp"

using namespace ariel;
Card::Card(Rank rank, Suit suit) {
    this->rank=rank;
    this->suit=suit;
}
Card::Card(const Card& other){
    this->rank=other.rank;
    this->suit=other.suit;
}
Card::Card() : rank(Rank::TWO), suit(Suit::SPADES) {}

std::string Card::rankToString() {
    switch (this->rank) {
        case TWO:
            return "Two";
        case THREE:
            return "Three";
        case FOUR:
            return "Four";
        case FIVE:
            return "Five";
        case SIX:
            return "Six";
        case SEVEN:
            return "Seven";
        case EIGHT:
            return "Eight";
        case NINE:
            return "Nine";
        case TEN:
            return "Ten";
        case JACK:
            return "Jack";
        case QUEEN:
            return "Queen";
        case KING:
            return "King";
        case ACE:
            return "Ace";
        default:
            return "Unknown rank";
    }
}

std::string Card::suitToString() {
    switch (this->suit) {
        case SPADES: return "Spades ";
        case HEARTS: return "Hearts ";
        case DIAMONDS: return "Diamonds ";
        case CLUBS: return "Clubs ";
        default: return "Unknown suit ";
    }
}
std::string Card::toString(){
    return (rankToString()+" of "+ suitToString());
}

