#include "player.hpp"

using namespace ariel;
Player::Player() {
    this->name="unknown";
    this->stackCards=NULL;
    this->takenCards=NULL;
}
Player::Player(std::string name){
    this->name=name;
    this->stackCards=NULL;
    this->takenCards=NULL;
}
