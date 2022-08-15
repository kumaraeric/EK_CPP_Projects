// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "Pack.h"
#include <array>
#include <string>
#include <cassert>

using namespace std;

Pack::Pack(){
    string suit; 
    for(int i =0;i<4;++i){
        if(i==0){
            suit = Card::SUIT_SPADES;
        }
        if(i==1){
            suit = Card::SUIT_HEARTS;
        }
        if(i==2){
            suit = Card::SUIT_CLUBS;
        }
        if(i==3){
            suit = Card::SUIT_DIAMONDS;
        }

        Pack::cards[0+6*i] = {Card::RANK_NINE,suit};
        Pack::cards[1+6*i] = {Card::RANK_TEN,suit};
        Pack::cards[2+6*i] = {Card::RANK_JACK,suit};
        Pack::cards[3+6*i] = {Card::RANK_QUEEN,suit};
        Pack::cards[4+6*i] = {Card::RANK_KING,suit};
        Pack::cards[5+6*i] = {Card::RANK_ACE,suit};
    }
    reset();
}

Pack::Pack(std::istream& pack_input){
    string rank_word, suit_word, useless_word;
    int counter = 0;  
    while(pack_input >> rank_word >> useless_word >> suit_word){
        cards[counter] = {rank_word,suit_word};
        counter++;
    }
    reset();
}

Card Pack::deal_one(){
    Card holder = cards[next];
    next++;
    return holder;
}

void Pack::reset(){
    next = 0;
}

bool Pack::empty() const{
if(next<=23 && 0<=next){
    return false;
}
    return true; 
}

void Pack::shuffle(){
    for(int i=0;i<7;++i){
        Pack holder; 
        for(int j=0;j<(PACK_SIZE)/2;++j){
            holder.cards[2*j] = cards[PACK_SIZE/2+j];
            holder.cards[1+2*j] = cards[j]; 
        }
        cards = holder.cards;
    }
    reset();
}
