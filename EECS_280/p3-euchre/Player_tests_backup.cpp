//Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include "unit_test_framework.h"
#include <sstream>
using namespace std;

TEST(test_player_factory){
    Player *simple = Player_factory("simple_player","Simple");
    Player *human = Player_factory("human_player","Human");
    ostringstream os1,os2; 

    os1 << *simple; 
    os2 << *human; 

    ASSERT_EQUAL(simple->get_name(),"simple_player");
    ASSERT_EQUAL(simple->get_name(),os1.str());
    ASSERT_EQUAL(human->get_name(),"human_player");
    ASSERT_EQUAL(human->get_name(),os2.str());

    delete human;
    delete simple;

}

TEST(test_led_no_trump){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;

    Card first = {Card::RANK_QUEEN,Card::SUIT_HEARTS};
    Card second = {Card::RANK_KING,Card::SUIT_HEARTS};
    Card third = {Card::RANK_ACE,Suit_next(trump)};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_EQUAL(simple->lead_card(trump),third);
    delete simple;


}

TEST(test_led_no_trump_one){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;

    Card first = {Card::RANK_QUEEN,Card::SUIT_HEARTS};
    simple->add_card(first);
    ASSERT_EQUAL(simple->lead_card(trump),first);
    delete simple;


}

TEST(test_play_no_trump_no_led){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = Card::SUIT_HEARTS;

    Card lead = {Card::RANK_TWO,lead_suit};

    Card first = {Card::RANK_SIX,Card::SUIT_DIAMONDS};
    Card second = {Card::RANK_THREE,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_JACK,Card::SUIT_SPADES};

    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,second);
    delete simple;
}

TEST(test_play_no_trump_no_led_one){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = Card::SUIT_HEARTS;

    Card lead = {Card::RANK_TWO,lead_suit};

    Card first = {Card::RANK_SIX,Card::SUIT_DIAMONDS};


    simple->add_card(first);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,first);
    delete simple;
}

//simple player
//cases where hand is entirely trump card
    //add card
    //lead card
    //add and discard card

    //cases with no led and no trumps for play and led


    //cases when hand is full (5)
    //all trump
TEST(test_simple_add_and_discard_upcard_lowest){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is hearts
    string trump = Card::SUIT_HEARTS;

    simple->add_card({Card::RANK_NINE,trump});
    simple->add_card({Card::RANK_TEN,trump});
    simple->add_card({Card::RANK_KING,trump});
    simple->add_card({Card::RANK_JACK,Suit_next(trump)});
    simple->add_card({Card::RANK_QUEEN,trump});
    

    simple->add_and_discard({Card::RANK_SIX,trump});

    Card lead = simple->lead_card(trump);

    Card check_1 = {Card::RANK_SIX,trump};
    Card check_2 = {Card::RANK_JACK,Suit_next(trump)};
    
    ASSERT_NOT_EQUAL(lead,check_1);
    ASSERT_EQUAL(lead,check_2);

    delete simple;
}
    //all trump
TEST(test_simple_add_and_discard_upcard_bower){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;

    Card first = {Card::RANK_THREE,trump};
    Card second = {Card::RANK_SIX,trump};
    Card third = {Card::RANK_SEVEN,trump};
    Card fourth = {Card::RANK_NINE,trump};
    Card fifth = {Card::RANK_QUEEN,trump};

    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);
    simple->add_card(fourth);
    simple->add_card(fifth);

    Card upcard = {Card::RANK_JACK,trump};
    simple->add_and_discard(upcard);

    Card lead = simple->lead_card(trump);
    ASSERT_EQUAL(lead,upcard);
    delete simple;
}

    //cases when hand is only 1

TEST(test_simple_add_and_discard_one_card){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;

    Card first = {Card::RANK_JACK,Suit_next(trump)};

    simple->add_card(first);

    Card upcard = {Card::RANK_ACE,trump};
    simple->add_and_discard(upcard);

    Card lead = simple->lead_card(trump);
    ASSERT_EQUAL(lead,first);
    delete simple;
}

//cases with mixed hands (trump and non-trump)

    //cases when hand is full(5)
    //trump and non-trump
TEST(test_simple_add_and_discard_mixed_hand){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;

    Card first = {Card::RANK_THREE,trump};
    Card second = {Card::RANK_SIX,trump};
    Card third = {Card::RANK_SEVEN,Card::SUIT_DIAMONDS};
    Card fourth = {Card::RANK_QUEEN,Card::SUIT_SPADES};
    Card fifth = {Card::RANK_NINE,Card::SUIT_HEARTS};

    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);
    simple->add_card(fourth);
    simple->add_card(fifth);

    Card upcard = {Card::RANK_JACK,trump};
    simple->add_and_discard(upcard);

    Card lead = simple->lead_card(trump);
    ASSERT_EQUAL(lead,fourth);
    delete simple;
}

    //cases when there is a tie
    //trump and non-trump
TEST(test_simple_add_and_discard_mixed_hand_tie){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;

    Card first = {Card::RANK_NINE,Card::SUIT_HEARTS};
    Card second = {Card::RANK_NINE,Card::SUIT_SPADES};
    Card third = {Card::RANK_NINE,Card::SUIT_DIAMONDS};

    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    Card upcard = {Card::RANK_TWO,trump};
    simple->add_and_discard(upcard);

    Card lead = simple->lead_card(trump);
    ASSERT_EQUAL(lead,third);
    delete simple;
}

    //cases when there is one card
TEST(test_simple_add_and_discard_mixed_one_card){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;

    Card first = {Card::RANK_JACK,Card::SUIT_DIAMONDS};

    simple->add_card(first);

    Card upcard = {Card::RANK_ACE,trump};
    simple->add_and_discard(upcard);

    Card lead = simple->lead_card(trump);
    ASSERT_EQUAL(lead,upcard);
    delete simple;
}

//testing trump
    //round 1
TEST(test_simple_make_trump_round_one_pass_with_3){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card upcard = {Card::RANK_TWO,trump};
    Card first = {Card::RANK_QUEEN,trump};
    Card second = {Card::RANK_KING,trump};
    Card third = {Card::RANK_JACK,Suit_next(trump)};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_TRUE(simple->make_trump(upcard,0,1,order_up_suit));
    ASSERT_EQUAL(order_up_suit,trump);

    delete simple;


}

TEST(test_simple_make_trump_round_one_pass_with_2){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card upcard = {Card::RANK_TWO,trump};
    Card first = {Card::RANK_QUEEN,Card::SUIT_DIAMONDS};
    Card second = {Card::RANK_KING,trump};
    Card third = {Card::RANK_JACK,trump};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_TRUE(simple->make_trump(upcard,0,1,order_up_suit));
    ASSERT_EQUAL(order_up_suit,trump);

    delete simple;


}

TEST(test_simple_make_trump_round_one_fail){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card upcard = {Card::RANK_TWO,trump};
    Card first = {Card::RANK_QUEEN,Card::SUIT_HEARTS};
    Card second = {Card::RANK_KING,Card::SUIT_HEARTS};
    Card third = {Card::RANK_JACK,Suit_next(trump)};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_FALSE(simple->make_trump(upcard,0,1,order_up_suit));

    delete simple;


}

    //round 2
    
TEST(test_simple_make_trump_round_two_fail){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card upcard = {Card::RANK_TWO,trump};
    Card first = {Card::RANK_QUEEN,trump};
    Card second = {Card::RANK_KING,trump};
    Card third = {Card::RANK_JACK,Card::SUIT_HEARTS};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_FALSE(simple->make_trump(upcard,0,2,order_up_suit));

    delete simple;


}

TEST(test_simple_make_trump_round_two_pass_1){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card upcard = {Card::RANK_TWO,trump};
    Card first = {Card::RANK_JACK,Suit_next(trump)};
    Card second = {Card::RANK_KING,trump};
    Card third = {Card::RANK_JACK,Card::SUIT_HEARTS};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_TRUE(simple->make_trump(upcard,0,2,order_up_suit));
    ASSERT_EQUAL(order_up_suit,Suit_next(trump));

    delete simple;


}

TEST(test_simple_make_trump_round_two_pass_2){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card upcard = {Card::RANK_TWO,trump};
    Card first = {Card::RANK_ACE,Suit_next(trump)};
    Card second = {Card::RANK_KING,trump};
    Card third = {Card::RANK_KING,Suit_next(trump)};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_TRUE(simple->make_trump(upcard,0,2,order_up_suit));
    ASSERT_EQUAL(order_up_suit,Suit_next(trump));

    delete simple;


}

TEST(test_simple_make_trump_round_two_pass_trumps){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card upcard = {Card::RANK_TWO,trump};
    Card first = {Card::RANK_JACK,Suit_next(trump)};
    Card second = {Card::RANK_JACK,trump};
    Card third = {Card::RANK_JACK,Card::SUIT_HEARTS};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_TRUE(simple->make_trump(upcard,0,2,order_up_suit));
    ASSERT_EQUAL(order_up_suit,Suit_next(trump));

    delete simple;


}

TEST(test_make_trump_screw_the_dealer){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;
    Card upcard = {Card::RANK_TWO,trump};

    ASSERT_TRUE(simple->make_trump(upcard,1,2,order_up_suit));
    ASSERT_EQUAL(order_up_suit,Suit_next(trump));

    delete simple;
}

//playing tricks

    //can follow suit
        //hand size is max


TEST(test_simple_playing_trick_basic){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = Card::SUIT_HEARTS;
    Card lead = {Card::RANK_TWO,lead_suit};

    Card second = {Card::RANK_SIX,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_JACK,lead_suit};
    Card fourth = {Card::RANK_ACE,lead_suit};
  

    simple->add_card(second);
    simple->add_card(third);
    simple->add_card(fourth);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,fourth);
    delete simple;
}

TEST(test_simple_playing_trick_led_trump_same_lb){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = trump;
    Card lead = {Card::RANK_TWO,lead_suit};

    Card first = {Card::RANK_THREE,trump};
    Card second = {Card::RANK_SIX,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_JACK,Suit_next(lead_suit)};
    Card fourth = {Card::RANK_ACE,lead_suit};
    Card fifth = {Card::RANK_NINE,lead_suit};

    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);
    simple->add_card(fourth);
    simple->add_card(fifth);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,third);
    delete simple;
}

TEST(test_simple_playing_trick_led_trump_same_rb_lb){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = trump;
    Card lead = {Card::RANK_TWO,lead_suit};

    Card first = {Card::RANK_JACK,trump};
    Card second = {Card::RANK_JACK,Suit_next(trump)};

    simple->add_card(first);
    simple->add_card(second);


    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,first);
    delete simple;
}

    //hand size is one 
TEST(test_simple_playing_trick_led_one){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = trump;
    Card lead = {Card::RANK_TWO,lead_suit};

    Card first = {Card::RANK_THREE,trump};
   

    simple->add_card(first);
 

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,first);
    delete simple;
}

TEST(test_simple_playing_trick_no_led_one){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = trump;
    Card lead = {Card::RANK_TWO,lead_suit};

    Card first = {Card::RANK_THREE,Card::SUIT_SPADES};
    simple->add_card(first);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,first);
    delete simple;
}

    //cannot follow suit

TEST(test_playing_lb_led_suit){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_DIAMONDS;
    string lead_suit = Card::SUIT_HEARTS;

    Card lead = {Card::RANK_TWO,lead_suit};

    Card first = {Card::RANK_JACK,Card::SUIT_HEARTS};
    Card second = {Card::RANK_SIX,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_TWO,Card::SUIT_HEARTS};

    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,third);
    delete simple;
}

TEST(test_simple_playing_trick_no_led_basic){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = Card::SUIT_HEARTS;

    Card lead = {Card::RANK_TWO,lead_suit};

    Card first = {Card::RANK_THREE,trump};
    Card second = {Card::RANK_SIX,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_JACK,Card::SUIT_SPADES};

    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,second);
    delete simple;
}

TEST(test_simple_playing_trick_no_led_tie){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = trump;

    Card lead = {Card::RANK_TWO,lead_suit};

    Card second = {Card::RANK_JACK,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_JACK,Card::SUIT_HEARTS};
    Card fourth = {Card::RANK_QUEEN,Card::SUIT_DIAMONDS};
    Card fifth = {Card::RANK_QUEEN,Card::SUIT_HEARTS};

    simple->add_card(second);
    simple->add_card(third);
    simple->add_card(fourth);
    simple->add_card(fifth);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,third);
    delete simple;
}

TEST(test_simple_playing_trick_no_led_bowers){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_HEARTS;
    string lead_suit = Card::SUIT_SPADES;

    Card lead = {Card::RANK_TWO,lead_suit};

    Card second = {Card::RANK_JACK,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_JACK,Card::SUIT_HEARTS};

    simple->add_card(second);
    simple->add_card(third);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,second);
    delete simple;
}

//human player



TEST_MAIN()