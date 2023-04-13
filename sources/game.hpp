#pragma once
#include "player.hpp"
#include <tuple>
#include <vector>
#include <queue>
#include <stack>

namespace ariel {
    class Game {
        private:
            Player& player1;
            Player& player2;
            std::queue<string> turns;
            std::vector<std::tuple<Player, Card, bool>>  statistics;
            std::stack<Card> cards;
            string winner;
            bool* hasWinner=new bool;
        public:
            Game(Player&, Player&);
            void playTurn();
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog();
            void printStats();
            void createDeckOfCards();
            void updateStats(Player&, Card&, bool&);
            void setWinner();

        };
    void shuffleCards(std::stack<Card>&, size_t);

}