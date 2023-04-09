#include "game.hpp"
#include "random"
using namespace ariel;


Game::Game(Player p1, Player p2){
    this->p1=p1;
    this->p2=p2;
    this->statistics=NULL;
    this->cards=new Card*[52];
    this->cards=createDeckOfCards(cards);
    shuffleCards(this->cards);
    for (int i = 0; i < 52 ; ++i) {
        if(i%2==0)p1.pushCardsTaken(*cards[i]);
        else p2.pushCardsTaken(*cards[i]);
    }
}
void Game::playTurn(){
    std::queue<Card*> table;
    while (p1.stacksize()>0) {
        Card *p1Card = p1.popStackCards();
        Card *p2Card = p2.popStackCards();
        table.push(p1Card);
        table.push(p2Card);
        if (*p1Card > *p2Card){
            p1.pushCardsTaken(p1Card);
            p1.pushCardsTaken(p2Card);
            pushTurnString(p1, p2);
            updateStats();
        } else if (*p1Card > *p2Card){
            p2.pushCardsTaken(p2Card);
            p2.pushCardsTaken(p1Card);
            pushTurnString(p1, p2);
            updateStats();
        } else {
            table.push(p1.popStackCards());
            table.push(p1.popStackCards());
            table.push(p2.popStackCards());
            table.push(p2.popStackCards());
        }
    }
}
void Game::printLastTurn(){}
void Game::playAll(){}
void Game::printWiner(){}
void Game::printLog(){}
void Game::printStats(){}
void Game::shuffleCards(Card * cards) {
    std::random_device rd;
    std::mt19937 rng(rd());
    for (size_t i = 0; i < 52; i++) {
        std::shuffle(&cards[i], rng);
    }
}
void Game::pushTurnString(Player p1, Player p2){
    this->turns.push("example ");
    //Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.
}

void Game::updateStats() {}

