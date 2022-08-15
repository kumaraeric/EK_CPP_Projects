// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include "Pack.h"
#include "Player.h"
#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class Game{
    private:
    vector<Player*> players;
    int hand = 0;
    Pack pack; 

    //teams
    // team 1 - player 0 and 2
    // team 2 - player 1 and 3
    int team_1_tricks = 0; 
    int team_2_tricks = 0;
    int team_1_score = 0;
    int team_2_score = 0;
    int order_up_team = 0;

    //hand specific
    int dealer_index = 0; 
    int led_index = 1; 

    Card upcard;
    string trump;

    public:

    void create_player(const vector<string> player_names,
    vector<string>player_types){
        for(int i =0;i<int(player_types.size());++i){
            Player *player = Player_factory(player_names[i],player_types[i]);
            players.push_back(player);
        }
    }

     void delete_player(){
        for(int i =0;i<int(players.size());++i){
           delete players[i];
        }
    }

    void create_pack(std::istream& pack_input){
        pack = Pack(pack_input);
    }

    void shuffle_or_not(const string shuffle_arg){
        if(shuffle_arg == "shuffle"){
            pack.shuffle();
        }
        else{
            pack.reset();
        }
    }

    void dealing(){
        int holder_index = get_dealer();
        for(int i=0;i<int(players.size());++i){
            holder_index++;

            if(holder_index>3){
                holder_index=0;
            }

            if(i==0 || i==2){
                players[holder_index]->add_card(pack.deal_one());
                players[holder_index]->add_card(pack.deal_one());
                players[holder_index]->add_card(pack.deal_one());
                
               
            }

            else{
                players[holder_index]->add_card(pack.deal_one());
                players[holder_index]->add_card(pack.deal_one());
            }

        }

        for(int i=0;i<int(players.size());++i){
            holder_index++;

            if(holder_index>3){
                holder_index=0;
            }

            if(i==0 || i==2){
                players[holder_index]->add_card(pack.deal_one());
                players[holder_index]->add_card(pack.deal_one());
               
            }

            else{
                players[holder_index]->add_card(pack.deal_one());
                players[holder_index]->add_card(pack.deal_one());
                players[holder_index]->add_card(pack.deal_one());
                
            }

        }
        
        //4 cards remain
        //setting upcard
        upcard = pack.deal_one();
        start_hand();

    }

    void start_hand(){
        //Hand 0
        //Adi deals
        //Jack of Diamonds turned up
        cout << "Hand " << hand << endl;
        cout << *players[dealer_index] << " deals" << endl;
        cout << upcard << " turned up" << endl;
    }

    void dealer_add_discard(int round){
        if(round==1){
            players[get_dealer()]->add_and_discard(upcard);
        }
    }

    void changing_order_up_team(int holder_index){
        if(holder_index%2==0){
            order_up_team = 1; 
        }
        if(holder_index%2==1){
            order_up_team  = 2;
        }
    }

    void making_trump(){
        int holder_index = get_dealer();

        for(int round = 1;round<3;++round){
            for(int i =0;i<int(players.size());++i){
                holder_index++;
                if(holder_index>3){
                    holder_index = 0;
                }

                if(players[holder_index]->make_trump(upcard,i==get_dealer(),round,trump)){
                    cout << *players[holder_index] << " orders up " <<trump <<  endl;
                    dealer_add_discard(round);
                    cout << "\n";
                    changing_order_up_team(holder_index);
                    return;
                }
                else{
                    cout << *players[holder_index] << " passes" << endl;
                }
            }
        }

    }

    void lead_and_play(){
        vector<Card> played_cards;
        Card led_card,play_card;
        

        if(team_1_tricks == 0 && team_2_tricks == 0){
            led_index = get_dealer()+1;
            if(led_index>3){
                led_index = 0;
            }
        }

        int holder_index = led_index;

        led_card = players[holder_index]->lead_card(trump);
        cout << led_card << " led by " << *players[holder_index] << endl;
        played_cards.push_back(led_card);

        for(int i = 0;i<int(players.size())-1;++i){
            holder_index++; 
            if(holder_index>3){
                holder_index = 0;
            }
            play_card = players[holder_index]->play_card(led_card,trump);
            played_cards.push_back(play_card);
            cout << play_card << " played by " << *players[holder_index] << endl;
        }

       int places_from_holder = trick_winner(led_card,played_cards);
       led_index = led_index + places_from_holder; 
       if(led_index>3){
           led_index = led_index % 4;
       }

       cout << *players[led_index] <<" takes the trick" << endl;
       cout << "\n";
       awarding_trick();
    }

    void awarding_trick(){
        if(led_index == 0 || led_index == 2){
            team_1_tricks++;
        }
        if(led_index == 1 || led_index == 3){
            team_2_tricks++;
        }
    }

    int trick_winner(Card led_card, const vector<Card> played_cards){
        Card highest= played_cards[0];
        int index = 0;
        for(int i =0;i<int(played_cards.size());++i){
            if(Card_less(highest,played_cards[i],led_card,trump)){
                highest = played_cards[i];
                index = i;
            }
        }
        return index;
    }

    void print_hand_winner(){
        if(team_1_tricks>team_2_tricks){
            cout << *players[0] << " and " << *players[2] << " win the hand" << endl;
        }
        else{
            cout << *players[1] << " and " << *players[3] << " win the hand" << endl;
        }
    }

    void awarding_points(){
        print_hand_winner();

        if((team_1_tricks == 3 || team_1_tricks == 4) && order_up_team == 1){
            team_1_score++;
        }

        else if((team_1_tricks == 5) && order_up_team == 1){
            team_1_score = team_1_score + 2;
            cout << "march!" << endl;

        }

        else if((team_1_tricks == 3 || team_1_tricks == 4 
        || team_1_tricks==5) && order_up_team == 2){
            team_1_score = team_1_score + 2;
            cout << "euchred!" << endl;
        }

        else if((team_2_tricks == 3 || team_2_tricks == 4) && order_up_team == 2){
            team_2_score++;
        }

        else if((team_2_tricks == 5) && order_up_team == 2){
            team_2_score = team_2_score + 2;
            cout << "march!" << endl;
        }

        else if((team_2_tricks == 3 || team_2_tricks == 4 
        || team_2_tricks==5) && order_up_team == 1){
            team_2_score = team_2_score + 2;
            cout << "euchred!" << endl;
        }

    }

    void print_points(){
        cout << *players[0] << " and " << *players[2] 
        << " have " << team_1_score << " points" << endl;
        cout << *players[1] << " and " << *players[3] 
        << " have " << team_2_score << " points" << endl;
        cout << "\n";
    }

    void next_dealer_hand(){
        dealer_index++;
        led_index = dealer_index + 1;
        hand++;
        if(dealer_index>3){
            dealer_index=0;
        }
        if(led_index>3){
            led_index=0;
        }
    }

    int get_dealer(){
        return dealer_index;
    }

    bool new_hand_condition(int const max_score){
        team_1_tricks = 0; 
        team_2_tricks = 0;
        if(team_1_score >= max_score || team_2_score >= max_score){
            return false;
        }

        return true;
    }

    void print_winers(){
        if(team_1_score > team_2_score){
            cout << *players[0] << " and " << *players[2] << " win!" << endl;
        }
        else{
            cout << *players[1] << " and " << *players[3] << " win!" << endl;
        }

    }

};

static bool condition_checking(string file_name, int const points, 
string shuffle_arg, vector<string>type){

    if(!(points>=1 && points<=100) || !(shuffle_arg == "shuffle" 
    || shuffle_arg == "noshuffle") || !(type[0]=="Human" || type[0] == "Simple") 
    || !(type[1]=="Human" || type[1] == "Simple") || !(type[2]=="Human" || 
    type[2] == "Simple") || !(type[3]=="Human" || type[3] == "Simple") ){
        return true
        ;
    }
    return false;
}

void print_exec(int argc, char *argv[]){
    string holder = "";
    for(int i=0;i<argc;++i){
        holder = holder + argv[i] + " ";
    }
    cout << holder << endl;
}

int main(int argc, char *argv []){

    vector<string>player_names = {argv[4],argv[6],argv[8],argv[10]};
    vector<string>player_types = {argv[5],argv[7],argv[9],argv[11]};
    string shuffle_arg = argv[2];
    int max_score = atoi(argv[3]);

    //condition checking
    if(argc!=12 || condition_checking(argv[1], max_score,
     shuffle_arg,player_types)){
         cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
     }

    //opening file
    ifstream fin;
    fin.open(argv[1]);
    if(!fin.is_open()){
        cout << "Error opening " << argv[1] << endl;
        return 1;
    }

    //initializing variables
    Game game; 
    game.create_player(player_names,player_types);
    game.create_pack(fin);
    print_exec(argc,argv);

    //setup for game
    while(game.new_hand_condition(max_score)){
        game.shuffle_or_not(shuffle_arg);
        game.dealing();
        game.making_trump();

        for(int i = 0;i<5;++i){
            game.lead_and_play();
        }

        game.awarding_points();
        game.print_points();
        game.next_dealer_hand();

    }
   
   game.print_winers();
    
    //deleting players
    game.delete_player();

    return 0;
}