//Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include <string>
#include <vector>
#include <cassert>
#include "Player.h"

using namespace std;
//static const int MAX_HAND_SIZE = 5;

class Simple: public Player{
    private:
    std::string name;
    std::vector<Card> hand; 
    
    public:

    Simple(std::string const name_in):name(name_in){}

   const std::string & get_name() const override{
        return name; 
    }

    void add_card(const Card &c) override{
        assert(int(hand.size())<MAX_HAND_SIZE);
        hand.push_back(c);
    }

   void add_and_discard(const Card &upcard)override{
       assert(hand.size()<=MAX_HAND_SIZE);
       assert(hand.size()>=1);
       Card lowest = upcard;
       int index;
       std::string trump = upcard.get_suit();

       for(int i = 0;i<int(hand.size());++i){
           if(Card_less(hand[i],lowest,trump)){
               lowest = hand[i];
               index = i;
           }
       }

        if(lowest!=upcard){
            hand.erase(hand.begin()+index);
            add_card(upcard);
        }

    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override{

        assert(round==1 || round ==2);

        if(round==1 && hand_face_count(upcard.get_suit())>=2){
          order_up_suit = upcard.get_suit();
          return true; 
        }
        if( round == 2 && hand_face_count(Suit_next(upcard.get_suit()))>=1){
          order_up_suit = Suit_next(upcard.get_suit());
          return true; 
        }

        if(is_dealer && round == 2){
              order_up_suit = Suit_next(upcard.get_suit());
              return true;
        }

        return false;
    }

    Card lead_card(const std::string &trump) override{
        assert(hand.size()<=MAX_HAND_SIZE);
        assert(hand.size()>=1);
        assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
         || trump == Card::SUIT_SPADES || trump == Card::SUIT_HEARTS);

        int trump_count = 0;
        Card lead_card;
        int index;

        for(int i=0;i<int(hand.size());++i){
            if(hand[i].is_trump(trump)){
                trump_count++;
            }
        }

        if(trump_count==int(hand.size())){
            lead_card = hand[0];
            index = 0;
            for(int i=0;i<int(hand.size());++i){
               if(Card_less(lead_card,hand[i],trump)){
                   lead_card = hand[i];
                   index = i;
               }
            }
        }

        else{
             std::vector<int> non_trump_index;
            for(int i=0;i<int(hand.size());++i){
                if(!hand[i].is_trump(trump)){
                    non_trump_index.push_back(i);
                }
            }

            lead_card = hand[non_trump_index[0]];
            index = non_trump_index[0];
            for(int i=0;i<int(non_trump_index.size());++i){
                if(Card_less(lead_card,hand[non_trump_index[i]],trump)){
                    lead_card = hand[non_trump_index[i]];
                    index = non_trump_index[i];
                }
            }
        }

        hand.erase(hand.begin()+index);
        return lead_card;

    }

    Card play_card(const Card &led_card, const std::string &trump) override {
        assert(hand.size()<=MAX_HAND_SIZE);
        assert(hand.size()>=1);
        assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
         || trump == Card::SUIT_SPADES || trump == Card::SUIT_HEARTS);
        
        std::vector<int> same_led_suit_index = {};

        if(led_card.get_suit()!=trump && !led_card.is_left_bower(trump)){
            for(int i=0;i<int(hand.size());++i){
                if(hand[i].get_suit()==led_card.get_suit() 
                && !hand[i].is_left_bower(trump)){
                    same_led_suit_index.push_back(i);
                }
            }
        }
        else{
            for(int i=0;i<int(hand.size());++i){
                if(hand[i].is_trump(trump)){
                    same_led_suit_index.push_back(i);
                }
            }
        }

        Card play_card;
        int index;

        if(same_led_suit_index.size()==0){
            play_card = hand[0]; 
            index = 0;
            for(int i=0;i<int(hand.size());++i){
                if(Card_less(hand[i],play_card,trump)){
                    play_card = hand[i];
                    index = i;
                }
            }
        }

        else{
            play_card = hand[same_led_suit_index[0]];
            index = same_led_suit_index[0];
            for(int i=0;i<int(same_led_suit_index.size());++i){
                if(Card_less(play_card,hand[same_led_suit_index[i]],trump)){
                    play_card = hand[same_led_suit_index[i]];
                    index = same_led_suit_index[i];
                }
            }
        }
        
        hand.erase(hand.begin()+index);

        // for(int i=0;i<int(hand.size());++i){
        //     cout << hand[i].get_rank() << " " << hand[i].get_suit() << endl;
        // }

        return play_card;

    }

    int hand_face_count(const std::string suit)const{
        int count = 0;
        Card right_bower{Card::RANK_JACK, suit};
        Card left_bower{Card::RANK_JACK, Suit_next(suit)};
        Card Ace {Card::RANK_ACE, suit};
        Card King {Card::RANK_KING, suit};
        Card Queen {Card::RANK_QUEEN, suit};

        for(int i =0;i<int(hand.size());++i){
            if(hand[i] == right_bower || hand[i]==left_bower || hand[i]==Ace
             || hand[i]==King || hand[i]==Queen){
                 count++;
            }
        }

        return count; 
    }

    virtual ~Simple() {}

};

class Human: public Player{
    private:
    std::string name; 
    std::vector<Card> hand; 

    public:
    
    Human(std::string const name_in):name(name_in){}

    const std::string & get_name() const override{
        return name; 
    }

    void add_card(const Card &c) override{
        assert(int(hand.size())<MAX_HAND_SIZE);
        hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override{

        assert(round == 1 || round == 2);
        const_cast<Human*>(this)->sort_hand();
        const_cast<Human*>(this)->print_hand();

        std::string decision;
        std::cout << "Human player " << get_name() 
        <<", please enter a suit, or \"pass\":" << endl; 
        std::cin >> decision;
        if(decision == "pass"){
            return false;
        }
        
        order_up_suit = decision;
        return true;
    }

    void add_and_discard(const Card &upcard)override{
        assert(hand.size()>=1);
        sort_hand();
        print_hand();
        int index;
        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << get_name() <<
        ", please select a card to discard:"<<endl;
        cin >> index;

        if(index==-1){
            return;
        }

        else{
            hand.erase(hand.begin()+index);
            add_card(upcard);
        }

    }

    Card play_card(const Card &led_card, const std::string &trump)override{
        assert(hand.size()>=1);
        assert(trump==Card::SUIT_CLUBS || trump==Card::SUIT_DIAMONDS 
        || trump ==Card::SUIT_HEARTS || trump == Card::SUIT_HEARTS);

        sort_hand();
        print_hand();
        int index;
        cout << "Human player " << get_name() <<", please select a card:"<<endl;
        cin >> index;

        Card play_card = hand[index];
        hand.erase(hand.begin()+index);
        return play_card;
    }

    Card lead_card(const std::string &trump)override{
        assert(hand.size()>=1);
        assert(trump==Card::SUIT_CLUBS || trump==Card::SUIT_DIAMONDS 
        || trump ==Card::SUIT_HEARTS || trump == Card::SUIT_HEARTS);

        sort_hand();
        print_hand();
        int index;
        cout << "Human player " << get_name() <<", please select a card:"<<endl;
        cin >> index;

        Card play_card = hand[index];
        hand.erase(hand.begin()+index);
        return play_card;

    }

    void print_hand(){
        for(int i = 0;i<int(hand.size());i++){
            std::cout <<"Human player " << name <<"'s hand: [" <<
            i<<"] "<< hand[i] << std::endl; 
        }
    }

    void sort_hand(){
        vector<Card>new_hand = hand;
        vector<int> index= {};
        for(int i =0;i<int(hand.size());++i){
            Card lowest = new_hand[0];
            int lowest_index = 0;
            for(int j =0;j<int(new_hand.size());++j){
                if(new_hand[j]<lowest){
                    lowest = new_hand[j];
                    lowest_index = j;
                }
            }
            hand[i] = lowest;
            new_hand.erase(new_hand.begin()+lowest_index);
        }

    }
    virtual ~Human(){}

};

Player * Player_factory(const std::string &name, const std::string &strategy){
      if (strategy == "Simple") {
         return new Simple(name);
      }
      if(strategy == "Human"){
          return new Human(name);
      }
      return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p){
   return os << p.get_name();
}