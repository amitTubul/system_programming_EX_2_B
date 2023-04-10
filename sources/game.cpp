#include "game.hpp"
#include "random"
#include <algorithm>
#include <iostream>

using namespace ariel;
using namespace std;

Game::Game(Player& p1, Player& p2) : p1(p1),p2(p2){
    this->statistics=NULL;
    this->hasWinner= false;
    createDeckOfCards();
    shuffleCards(this->cards, 52);
    for (int i = 0; i < 52 ; ++i) {
        if(i%2==0)p1.pushStackCards(cards.top());
        else p2.pushStackCards(cards.top());
        cards.pop();
    }
}
void Game::playTurn(){
    if (this->hasWinner)throw runtime_error("game is already over");
    if (&p1==&p2)throw invalid_argument("player cannot play with himself");
    std::stack<Card> table;
    string move("");
    while (p1.stacksize()>0) {
        Card p1Card = p1.topStackCards();
        Card p2Card = p2.topStackCards();
        p1.popStackCards();
        p2.popStackCards();
        table.push(p1Card);
        table.push(p2Card);
        move.append((p1.getName()+" played "+ p1Card.toString() + p2.getName() + " played " + p2Card.toString()+". "));
        if (p1Card > p2Card){
            while(!table.empty()){
                p1.pushCardsTaken(table.top());
                table.pop();
            }
            move.append(p1.getName()+" wins.");
            this->turns.push(move);
            updateStats();
            if(p1.stacksize()==0){
                this->hasWinner= true;
                this->winner=p1.getName();
            }
            return;
        } else if (p1Card < p2Card){
            while(!table.empty()) {
                p2.pushCardsTaken(table.top());
                table.pop();
            }
            move.append((p2.getName()+" wins."));
            this->turns.push(move);
            updateStats();
            if(p1.stacksize()==0){
                this->hasWinner= true;
                this->winner=p2.getName();
            }
            return;
        } else {
            if(p1.stacksize()==0)break;
            table.push(p1.topStackCards());
            table.push(p2.topStackCards());
            p1.popStackCards();
            p2.popStackCards();
            move.append("draw. ");
        }
    }
    shuffleCards(table,table.size());
    while(!table.empty()){
        p2.pushStackCards(table.top());
        p1.pushCardsTaken(table.top());
        table.pop();
        table.pop();
    }
    move.append("draw. restart");
    this->turns.push(move);
}
void Game::printLastTurn(){cout << this->turns.front() << endl;}
void Game::playAll(){while(!hasWinner) playTurn();}
void Game::printWiner(){
    if(this->hasWinner)cout << this->winner << endl;
    else cout << "there is no winner yet" << endl;
}
void Game::printLog(){
    int size=this->turns.size();
    while(size>0){
        string *temp=new string (turns.front());
        cout << *temp << endl;
        turns.pop();
        this->turns.push(*temp);
        size--;
    }
}
void Game::printStats(){}
void Game::createDeckOfCards(){
    for (int i = static_cast<int>(Rank::TWO); i <= static_cast<int>(Rank::ACE); ++i) {
        for (int j = static_cast<int>(Suit::SPADES); j <= static_cast<int>(Suit::CLUBS); ++j) {
            const Card temp(static_cast<Rank>(i), static_cast<Suit>(j));
            this->cards.push(temp);
        }
    }
}

void Game::updateStats() {}

void ariel::shuffleCards(std::stack<Card>& cards, size_t size) {
    std::vector<Card> tempCards;
    while(!cards.empty()){
        tempCards.push_back(cards.top());
        cards.pop();
    }
    std::random_device rd;
    std::shuffle(tempCards.begin(), tempCards.end(), rd);

    size = std::min(size, tempCards.size());
    for (size_t j = 0; j < size; ++j) {
        cards.push(tempCards[j]);
    }
}

