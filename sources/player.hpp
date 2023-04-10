#pragma once
#include "string"
#include "card.hpp"
#include <stack>

using namespace std;

namespace ariel{
    class Player {
        private:
            string name;
            std::stack<Card> stackCards; // stack of cards
            std::stack<Card> takenCards; // stack of taken cards
        public:
            Player();
            Player(const string&);
            //Player(Player&);
            int stacksize();
            int cardesTaken();
            void pushStackCards(Card&);
            void pushCardsTaken(Card&);
            void popStackCards();
            Card topStackCards();
            string getName();
    };

}
