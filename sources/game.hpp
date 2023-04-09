#pragma once
#include "player.hpp"
#include <queue>
#include <string>

namespace ariel {
    class Game {
        private:
            Player p1;
            Player p2;
            std::queue<string> turns;
            std::string * statistics;
            Card * cards;
        public:
            Game(Player, Player){}
            void playTurn(){}
            void printLastTurn(){}
            void playAll(){}
            void printWiner(){}
            void printLog(){}
            void printStats(){}
            void shuffleCards(Card*){}
            void createDeckOfCards(){
                int size=0;
                for (int i = 1; i < 14 ; ++i) {
                    for (int j = 1; j < 5; ++j) {
                        cards[size] = new Card*(i, j);
                        size++;
                    }
                }
            }
            void pushTurnString(Player p1, Player p2){}
            void updateStats(){}

        };

}