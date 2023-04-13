#include "player.hpp"

using namespace ariel;

Player::Player(const string& name) : name(name){}
int Player::stacksize(){return this->stackCards.size();}
int Player::cardesTaken(){return this->takenCards.size();}
void Player::pushStackCards(Card& card){this->stackCards.push(card);}
void Player::pushCardsTaken(Card& card){this->takenCards.push(card);}
void Player::popStackCards(){stackCards.pop();}
void Player::popCardsTaken(){takenCards.pop();}
Card Player::topStackCards(){return stackCards.top();}
string Player::getName(){return this->name;}
