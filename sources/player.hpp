#pragma once
#include "string"
#include "card.hpp"
#include <stack>

using namespace std;

namespace ariel{
    class Player {
        private:
            std::string name;
            std::stack<Card*> stackCards;
            std::stack<Card*> takenCards; // array of taken cards
        public:
            Player(){}
            Player(std::string){}
            int stacksize(){return this->stackCards.size();}
            int cardesTaken(){return this->takenCards.size();}
            void pushStackCards(Card* card){this->stackCards.push(card);}
            void pushCardsTaken(Card* card){this->takenCards.push(card);}
            Card* popStackCards(){return stackCards.pop();}
    };

}
