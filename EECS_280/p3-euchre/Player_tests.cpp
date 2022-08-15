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

//making trump

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
    Card first = {Card::RANK_QUEEN,trump};
    Card second = {Card::RANK_JACK,Suit_next(trump)};


    simple->add_card(first);
    simple->add_card(second);

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

TEST(test_simple_make_trump_round_two_fail_next_suit_present){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card upcard = {Card::RANK_TWO,trump};
    Card first = {Card::RANK_TWO,Suit_next(trump)};
    Card second = {Card::RANK_THREE,Suit_next(trump)};
    Card third = {Card::RANK_JACK,Card::SUIT_HEARTS};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_FALSE(simple->make_trump(upcard,0,2,order_up_suit));

    delete simple;


}

TEST(test_simple_make_trump_round_two_pass_1_lb){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card upcard = {Card::RANK_TWO,trump};
    Card first = {Card::RANK_JACK,trump};
    Card second = {Card::RANK_KING,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_JACK,Card::SUIT_HEARTS};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_TRUE(simple->make_trump(upcard,0,2,order_up_suit));
    ASSERT_EQUAL(order_up_suit,Suit_next(trump));

    delete simple;


}

TEST(test_simple_make_trump_round_two_pass_1_rb){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card upcard = {Card::RANK_TWO,trump};
    Card first = {Card::RANK_JACK,Suit_next(trump)};
    Card second = {Card::RANK_KING,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_JACK,Card::SUIT_HEARTS};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_TRUE(simple->make_trump(upcard,0,2,order_up_suit));
    ASSERT_EQUAL(order_up_suit,Suit_next(trump));

    delete simple;


}

TEST(test_simple_make_trump_round_two_pass_1_other){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card upcard = {Card::RANK_TWO,trump};
    Card first = {Card::RANK_ACE,Suit_next(trump)};
    Card second = {Card::RANK_KING,trump};


    simple->add_card(first);
    simple->add_card(second);

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
    Card first = {Card::RANK_QUEEN,Suit_next(trump)};
    Card second = {Card::RANK_KING,Suit_next(trump)};
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

//adding and discarding

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

//leading 

TEST(test_lead_only_trump){
     Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card first = {Card::RANK_QUEEN,trump};
    Card second = {Card::RANK_JACK,Suit_next(trump)};
    Card third = {Card::RANK_TEN,trump};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_EQUAL(simple->lead_card(trump),second);

    delete simple;
}

TEST(test_lead_only_non_trump){
     Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card first = {Card::RANK_QUEEN,Card::SUIT_DIAMONDS};
    Card second = {Card::RANK_TEN,Card::SUIT_SPADES};
    Card third = {Card::RANK_TEN,Card::SUIT_HEARTS};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_EQUAL(simple->lead_card(trump),first);

    delete simple;
}

TEST(test_lead_only_mixed_tie){
     Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card first = {Card::RANK_QUEEN,trump};
    Card second = {Card::RANK_TEN,Card::SUIT_SPADES};
    Card third = {Card::RANK_TEN,Card::SUIT_HEARTS};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_EQUAL(simple->lead_card(trump),third);

    delete simple;
}

TEST(test_lead_only_mixed_normal){
     Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string order_up_suit;

    Card first = {Card::RANK_QUEEN,trump};
    Card second = {Card::RANK_TEN,Card::SUIT_SPADES};
    Card third = {Card::RANK_ACE,Card::SUIT_HEARTS};


    simple->add_card(first);
    simple->add_card(second);
    simple->add_card(third);

    ASSERT_EQUAL(simple->lead_card(trump),third);

    delete simple;
}

//playing 
// trump and led are different

TEST(test_play_basic){
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

//cannot follow suit

TEST(test_play_no_led){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = Card::SUIT_HEARTS;
    Card lead = {Card::RANK_TWO,lead_suit};

    Card second = {Card::RANK_QUEEN,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_JACK,trump};
    Card fourth = {Card::RANK_ACE, Card::SUIT_SPADES};
  

    simple->add_card(second);
    simple->add_card(third);
    simple->add_card(fourth);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,second);
    delete simple;
}


//trump and led are same

TEST(test_play_same_basic){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = trump;
    Card lead = {Card::RANK_TWO,lead_suit};

    Card one = {Card::RANK_FOUR,trump};
    Card second = {Card::RANK_QUEEN,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_THREE,trump};
    Card fourth = {Card::RANK_ACE, Card::SUIT_SPADES};
  

    simple->add_card(one);
    simple->add_card(second);
    simple->add_card(third);
    simple->add_card(fourth);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,one);
    delete simple;
}

TEST(test_play_same){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = trump;
    Card lead = {Card::RANK_TWO,lead_suit};

    Card one = {Card::RANK_FOUR,trump};
    Card second = {Card::RANK_QUEEN,Card::SUIT_DIAMONDS};
    Card third = {Card::RANK_JACK,Suit_next(trump)};
    Card fourth = {Card::RANK_ACE, Card::SUIT_SPADES};
  

    simple->add_card(one);
    simple->add_card(second);
    simple->add_card(third);
    simple->add_card(fourth);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,third);
    delete simple;
}


//led is lb of trump

TEST(test_play_same_led_lb){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = trump;
    Card lead = {Card::RANK_JACK,Suit_next(lead_suit)};

    Card one = {Card::RANK_FOUR,trump};
    Card second = {Card::RANK_QUEEN,Suit_next(lead_suit)};
    Card third = {Card::RANK_THREE,trump};
    Card fourth = {Card::RANK_ACE,Suit_next(lead_suit)};
  

    simple->add_card(one);
    simple->add_card(second);
    simple->add_card(third);
    simple->add_card(fourth);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,one);
    delete simple;
}

TEST(test_play_same_led_lb_only){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = trump;
    Card lead = {Card::RANK_JACK,Suit_next(lead_suit)};

    Card one = {Card::RANK_FOUR,Suit_next(lead_suit)};
    Card second = {Card::RANK_QUEEN,Suit_next(lead_suit)};
    Card third = {Card::RANK_THREE,trump};
    Card fourth = {Card::RANK_ACE,Suit_next(lead_suit)};
  

    simple->add_card(one);
    simple->add_card(second);
    simple->add_card(third);
    simple->add_card(fourth);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,third);
    delete simple;
}

TEST(test_play_same_led_lb_other_suit){
    Player *simple = Player_factory("simple_player","Simple");
    //trump suit is clubs
    string trump = Card::SUIT_CLUBS;
    string lead_suit = trump;
    Card lead = {Card::RANK_JACK,Suit_next(lead_suit)};

    Card one = {Card::RANK_FOUR,Suit_next(lead_suit)};
    Card second = {Card::RANK_QUEEN,Suit_next(lead_suit)};
    Card third = {Card::RANK_TWO,Suit_next(lead_suit)};
    Card fourth = {Card::RANK_ACE,Suit_next(lead_suit)};
  

    simple->add_card(one);
    simple->add_card(second);
    simple->add_card(third);
    simple->add_card(fourth);

    Card play = simple->play_card(lead,trump);
    ASSERT_EQUAL(play,third);
    delete simple;
}


TEST_MAIN()