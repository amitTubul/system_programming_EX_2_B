#pragma once
#include "player.hpp"
#include <queue>
#include <string>

namespace ariel {
    class Game {
        private:
            Player& p1;
            Player& p2;
            std::queue<string> turns;
            std::string * statistics;
            std::stack<Card> cards;
            string winner;
            bool hasWinner;
        public:
            Game(Player&, Player&);
            void playTurn();
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog();
            void printStats();
            void createDeckOfCards();
            void pushTurnString(string, string, string);
            void updateStats();
            std::string getWinner(){
                if(this->hasWinner)return this->winner;
                return NULL;
            }

        };
    void shuffleCards(std::stack<Card>&, size_t);

}