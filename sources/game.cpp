#include "game.hpp"
#include "random"
#include <algorithm>
#include <iostream>

using namespace ariel;
using namespace std;

Game::Game(Player& player1, Player& player2) : player1(player1),player2(player2){
    *(this->hasWinner)= false;
    createDeckOfCards();
}
//plays turn with the two players, can be 26 turns at once
void Game::playTurn(){
    if (*(this->hasWinner))throw runtime_error("game is already over");
    if (&player1==&player2)throw invalid_argument("player cannot play with himself");

    std::stack<Card> table;
    string move("");
    bool draw=false;
    //assuming player1.stacksize()==player2.stacksize()
    while (player1.stacksize()>0) {
        //moving cards to the table stack
        Card p1Card = player1.topStackCards();
        Card p2Card = player2.topStackCards();
        player1.popStackCards();
        player2.popStackCards();
        table.push(p1Card);
        table.push(p2Card);
        move.append((player1.getName()+" played "+ p1Card.toString() + player2.getName() + " played " + p2Card.toString()+". "));
        //player1 wins the round
        if (p2Card < p1Card){
            //player1 collect the table cards
            while(!table.empty()){
                player1.pushCardsTaken(table.top());
                table.pop();
            }
            move.append(player1.getName()+" wins.");
            this->turns.push(move);
            updateStats(player1,p1Card, draw);
            if(player1.stacksize()==0){
                setWinner();
            }
            return;
        }
        //player2 wins the round
        else if (p1Card < p2Card){
            //player1 collect the table cards
            while(!table.empty()) {
                player2.pushCardsTaken(table.top());
                table.pop();
            }
            move.append((player2.getName()+" wins."));
            this->turns.push(move);
            updateStats(player2,p2Card,draw);
            if(player1.stacksize()==0){
                setWinner();
            }
            return;
        }
        //draw between cards
        else{
            if(player1.stacksize()==0) {
                player1.pushCardsTaken(table.top());
                player2.pushCardsTaken(table.top());
                table.pop();
                setWinner();
                return;
            }
            //putting 2 cards on table
            table.push(player1.topStackCards());
            table.push(player2.topStackCards());
            player1.popStackCards();
            player2.popStackCards();
            move.append("draw. ");
            updateStats(player1,p2Card,draw=true);
        }
    }
    //here, there is a stackSize==0 to both players, it will shuffle the cards and
    //call playTurn recursively
    shuffleCards(table,table.size());
    while(!table.empty()){
        Card card1=table.top();
        table.pop();
        Card card2=table.top();
        table.pop();
        player2.pushStackCards(card1);
        player1.pushStackCards(card2);
    }
    move.append("draw. restart");
    this->turns.push(move);
    playTurn();
}
//all turns are recorded into "turns" queue
void Game::printLastTurn(){cout << this->turns.front() << endl;}
//play all games until there is a winner
void Game::playAll(){while(!*(this->hasWinner)) playTurn();}
//winner is provided after the game is finished
void Game::printWiner(){
    if(*(this->hasWinner))cout << "the winner is: "<< this->winner << endl;
    else cout << "there is no winner yet" << endl;
}
//prints turns by order
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
//stats are printed at any time the client wants, it all stored on vector of tuples
void Game::printStats(){
    double p1WinRate=0;
    double p2WinRate=0;
    double drawRate=0;
    for (unsigned long i = 0; i < statistics.size(); ++i) {
        if(!(std::get<2>(statistics[i]))) {
            if ((std::get<0>(statistics[i])).getName()==player1.getName()){
                p1WinRate++;
            }
            else p2WinRate++;
            (std::get<1>(statistics[i])).toString();
        }
        else drawRate++;
    }
    p1WinRate=(p1WinRate/statistics.size())*100;
    p2WinRate=(p2WinRate/statistics.size())*100;
    drawRate=(drawRate/statistics.size())*100;
    cout<<"========================================================================================"<<endl;
    cout<<"\nstatistics:"<<endl;
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    cout<<player1.getName()<<" won at: "<<p1WinRate<<"%"<<endl;
    cout<<player2.getName()<<" won at: "<<p2WinRate<<"%"<<endl;
    cout<<"draw rate is: "<<drawRate<<"%\n"<<endl;
    cout<<"cards won: "<<endl;
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    for (unsigned long i = 0; i < statistics.size(); ++i) {
        cout<<(std::get<1>(statistics[i])).toString()<<endl;
    }
    cout<<"========================================================================================"<<endl;
}
//helps to constructor, it will create a stack of 52 cards and shuffle it and then give it to players
void Game::createDeckOfCards(){
    //if the players has cards from previous game, we initialise it
    while(this->player1.cardesTaken()!=0){
        this->player1.popCardsTaken();
    }
    while(this->player2.cardesTaken()!=0){
        this->player2.popCardsTaken();
    }
    while(this->player1.stacksize()!=0){
        this->player1.popStackCards();
    }
    while(this->player2.cardesTaken()!=0){
        this->player2.popCardsTaken();
    }
    for (int i = static_cast<int>(Rank::TWO); i <= static_cast<int>(Rank::ACE); ++i) {
        for (int j = static_cast<int>(Suit::SPADES); j <= static_cast<int>(Suit::CLUBS); ++j) {
            Card temp(static_cast<Rank>(i), static_cast<Suit>(j));
            this->cards.push(temp);
        }
    }
    shuffleCards(this->cards, 52);
    //give the players they stack cards
    for (int i = 0; i < 52 ; ++i) {
        if(i%2==0)player1.pushStackCards(cards.top());
        else player2.pushStackCards(cards.top());
        cards.pop();
    }
}
//a function helps to update the stats on the tuple vector
void Game::updateStats(Player& roundWinner, Card& winningCard, bool& draw) {
    this->statistics.push_back(std::make_tuple(roundWinner, winningCard, draw));
}
//shuffle the cards, it takes a stack and move it to a vector, then, shuffle and returning the
//cards to thr stack
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
//the winner is set bt amount of cards taken while the game
void Game::setWinner() {
    *(this->hasWinner) = true;
    if(player1.cardesTaken()>player2.cardesTaken()) {
        this->winner = this->player1.getName();
    }
    else if(player2.cardesTaken()>player1.cardesTaken()) {
        this->winner = this->player2.getName();
    }
    else {
        this->winner = "Draw";
    }
}