// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"

using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
// member functions
Card::Card():rank(RANK_TWO),suit(SUIT_SPADES) {}

Card::Card(const std::string &rank_in, const std::string &suit_in)
:rank(rank_in),suit(suit_in){
    assert(suit_in ==SUIT_SPADES || suit_in ==SUIT_HEARTS ||
    suit_in == SUIT_CLUBS ||suit_in == SUIT_DIAMONDS);

    assert(rank_in == RANK_TWO || rank_in == RANK_THREE ||rank_in == RANK_FOUR ||
    rank_in == RANK_FIVE ||rank_in == RANK_SIX || rank_in == RANK_SEVEN 
    || rank_in == RANK_EIGHT || rank_in == RANK_NINE || 
    rank_in == RANK_TEN || rank_in == RANK_JACK || rank_in == RANK_QUEEN || 
    rank_in == RANK_KING || rank_in == RANK_ACE);
}

std::string Card::get_rank() const{
    return rank; 
}

std::string Card::get_suit()const{
    return suit;
}

bool Card::is_face() const{
    if(get_rank() == RANK_JACK || get_rank() == RANK_QUEEN || 
    get_rank() == RANK_KING || get_rank() == RANK_ACE){
        return true;
    }
    return false;
}

bool Card::is_trump(const std::string &trump) const{
    assert(trump == SUIT_CLUBS || trump == SUIT_HEARTS || 
    trump == SUIT_DIAMONDS ||  trump == SUIT_SPADES);

    if(get_suit() == trump || 
    (Suit_next(get_suit()) == trump && get_rank() == RANK_JACK)){
         return true;
    }
    return false;
 }

 std::string Card::get_suit(const std::string &trump) const{
     if(is_trump(trump)){
         return trump; 
     }
     return get_suit();
 }

bool Card::is_right_bower(const std::string &trump) const{
    assert(trump == SUIT_CLUBS || trump == SUIT_HEARTS || trump == SUIT_DIAMONDS ||
      trump == SUIT_SPADES);
    if(is_trump(trump) && get_rank() == RANK_JACK && get_suit() == trump){
        return true;
    }
    return false;
}

bool Card::is_left_bower(const std::string &trump) const{
    assert(trump == SUIT_CLUBS || trump == SUIT_HEARTS || trump == SUIT_DIAMONDS ||
      trump == SUIT_SPADES);
    if(is_trump(trump)  && get_rank() == RANK_JACK && get_suit() == Suit_next(trump)){
        return true;
    }
    return false;
   }

//bool operators

static void converting_rank_to_int(int &hs_value, const Card &hs){
    for(int i=0;i<NUM_RANKS;++i){
        if(hs.get_rank()==RANK_NAMES_BY_WEIGHT[i]){
            hs_value = i+1;
        }
    }    
}

static void converting_suit_to_int(int &hs_suit_int, const Card &hs){
    for(int i=0;i<NUM_SUITS;++i){
        if(hs.get_suit()==SUIT_NAMES_BY_WEIGHT[i]){
            hs_suit_int = i+1; 
        }   
    }
}

bool operator<(const Card &lhs, const Card &rhs){
    int lhs_rank_int, rhs_rank_int, lhs_suit_int, rhs_suit_int;
    converting_rank_to_int(lhs_rank_int,lhs);
    converting_rank_to_int(rhs_rank_int,rhs);
    converting_suit_to_int(lhs_suit_int,lhs);
    converting_suit_to_int(rhs_suit_int,rhs);

    if(lhs_rank_int < rhs_rank_int){
        return true;
    }

    else if(lhs_rank_int == rhs_rank_int){
        if(lhs_suit_int < rhs_suit_int){
            return true;
        }
        else if(lhs_suit_int > rhs_suit_int){
            return false;
        }
    }
    return false;
}

bool operator<=(const Card &lhs, const Card &rhs){
    int lhs_rank_int, rhs_rank_int, lhs_suit_int, rhs_suit_int;
    converting_rank_to_int(lhs_rank_int,lhs);
    converting_rank_to_int(rhs_rank_int,rhs);
    converting_suit_to_int(lhs_suit_int,lhs);
    converting_suit_to_int(rhs_suit_int,rhs);
    if((lhs < rhs) || ((lhs_rank_int
     == rhs_rank_int) && (lhs_suit_int == rhs_suit_int)) ){
        return true;
    }
   
    return false; 
}

bool operator>(const Card &lhs, const Card &rhs){
    if(!(lhs<=rhs)){
        return true;
    }
 
    return false; 
}

bool operator>=(const Card &lhs, const Card &rhs){
    if(!(lhs < rhs)){
        return true;
    }

    return false; 
}

bool operator==(const Card &lhs, const Card &rhs){
    if((lhs<=rhs)&&(lhs>=rhs)){
        return true;
    }
    return false; 
}

bool operator!=(const Card &lhs, const Card &rhs){
    if(!(lhs==rhs)){
        return true;
    }
    return false; 
}

//non-bool operators

std::string Suit_next(const std::string &suit){
    if(suit == Card::SUIT_CLUBS){
        return Card::SUIT_SPADES; 
    }
    if(suit == Card::SUIT_SPADES){
        return Card::SUIT_CLUBS;
    }
    if(suit == Card::SUIT_HEARTS){
        return Card::SUIT_DIAMONDS;
    }
    return Card::SUIT_HEARTS;

}

std::ostream & operator<<(std::ostream &os, const Card &card){
    os << card.get_rank() <<" of " << card.get_suit();
    return os; 
}

// including trump/led suit cases

bool Card_less(const Card &a, const Card &b, const string &trump){
    assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_HEARTS 
    || trump == Card::SUIT_DIAMONDS || trump == Card::SUIT_SPADES); 
    //case where either a or b is a trump
    if(b.is_trump(trump) || a.is_trump(trump)){
      //both are trumps
      if(b.is_trump(trump) && a.is_trump(trump)){
          if(a.is_right_bower(trump)){
              return false;
          }
          else if(b.is_right_bower(trump)){
              return true;
          }
          else if(a.is_left_bower(trump)){
              return false;
          }
          else if(b.is_left_bower(trump)){
              return true;
          }
          else if(a<b){
              return true; 
          }
          else if(a>b){
              return false;
          }
      }
      //if a is trump only
      else if(a.is_trump(trump) && !(b.is_trump(trump))){
          return false;
      }

      //if b is trump only
      
      else if(b.is_trump(trump) && !(a.is_trump(trump))){
          return true;
      }
    }
    //case where neither is a trump value
    else{
        if(a<b){
            return true; 
        }
        else if(a>b){
            return false;
        }
    }
    return false;
}

bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){

    assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_HEARTS 
    || trump == Card::SUIT_DIAMONDS ||trump == Card::SUIT_SPADES); 
    //included cases of only a trump, only b trump and if both are trump
    // A - B
    // trump - trump
    // trump - neither
    // trump - led
    // led - trump
    // neither - trump
    if(a.is_trump(trump) || b.is_trump(trump)){
        return Card_less(a,b,trump);
    }
   //led - neither
    else if(a.get_suit()==led_card.get_suit() && b.get_suit()!=led_card.get_suit()){
        return false;
    }

    //neither - led
    else if(b.get_suit()==led_card.get_suit() && a.get_suit()!=led_card.get_suit()){
        return true;
    }

    //led - led
    else if(a.get_suit()==led_card.get_suit() && b.get_suit()==led_card.get_suit()){
        if(a < b){
            return true;
        }
        if (a > b){
            return false;
        }
    }

    //neither - neither
    else if(a.get_suit()!=led_card.get_suit() && b.get_suit()!=led_card.get_suit()){
        if(a < b){
            return true;
        }
        if (a > b){
            return false;
        }
    }
    
    return false;
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
