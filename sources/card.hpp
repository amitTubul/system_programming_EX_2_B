#pragma once
#include <string>

namespace ariel{
    enum Rank{TWO=1, THREE=2, FOUR=3, FIVE=4, SIX=5, SEVEN=6, EIGHT=7, NINE=8, TEN=9,
        JACK=10, QUEEN=11, KING=12, ACE=13};
    enum Suit{SPADES=1, HEARTS=2, DIAMONDS=3, CLUBS=4};

    class Card {
        private:
            Rank rank;
            Suit suit;
        public:
            Card();
            Card(Rank, Suit);
            Card(const Card&);
            std::string rankToString();
            std::string suitToString();
            std::string toString();
            bool operator<(const Card& c2) {
                if(this->rank == ACE && c2.rank == TWO) {
                    return true;
                }
                return this->rank < c2.rank;
            }
            bool operator>(const Card& c2) {
                if(this->rank == ACE && c2.rank == TWO) {
                    return true;
                }
                return this->rank > c2.rank;
            }

    };
}