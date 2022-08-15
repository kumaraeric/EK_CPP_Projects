// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;
//member function tests

TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_card_default_ctor) {
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

TEST(test_is_face){
    Card a(Card::RANK_ACE,Card::SUIT_CLUBS);
    Card b(Card::RANK_KING,Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TEN,Card::SUIT_SPADES);
    Card d(Card::RANK_TWO,Card::SUIT_HEARTS);
    ASSERT_TRUE(a.is_face());
    ASSERT_TRUE(b.is_face());
    ASSERT_FALSE(c.is_face());
    ASSERT_FALSE(d.is_face());
}

TEST(test_is_trump){
    string trump = Card::SUIT_CLUBS; 
    Card a = {Card::RANK_FIVE, Card::SUIT_CLUBS};
    Card b = {Card::RANK_JACK,Card::SUIT_SPADES};
    Card c = {Card::RANK_FOUR, Card::SUIT_HEARTS};
    Card d = {Card::RANK_KING, Card::SUIT_SPADES};
    ASSERT_TRUE(a.is_trump(trump));
    ASSERT_TRUE(b.is_trump(trump));
    ASSERT_FALSE(c.is_trump(trump));
    ASSERT_FALSE(d.is_trump(trump));
}

TEST(test_get_suit){
    string trump = Card::SUIT_CLUBS; 
    Card a = {Card::RANK_FIVE, Card::SUIT_CLUBS};
    Card b = {Card::RANK_JACK,Card::SUIT_SPADES};
    Card c = {Card::RANK_FOUR, Card::SUIT_HEARTS};
    Card d = {Card::RANK_KING, Card::SUIT_SPADES};
    ASSERT_EQUAL(a.get_suit(trump),trump); 
    ASSERT_EQUAL(b.get_suit(trump),trump); 
    ASSERT_EQUAL(c.get_suit(trump),Card::SUIT_HEARTS); 
    ASSERT_EQUAL(d.get_suit(trump),Card::SUIT_SPADES); 
}

TEST(test_right_bower){
    string trump = Card::SUIT_HEARTS; 
    Card a (Card::RANK_JACK,Card::SUIT_HEARTS);
    Card b (Card::RANK_JACK,Card::SUIT_DIAMONDS);
    Card c (Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(a.is_right_bower(trump));
    ASSERT_FALSE(b.is_right_bower(trump));
    ASSERT_FALSE(c.is_right_bower(trump));
}

TEST(test_left_bower){
    string trump = Card::SUIT_HEARTS; 
    Card a (Card::RANK_JACK,Card::SUIT_HEARTS);
    Card b (Card::RANK_JACK,Card::SUIT_DIAMONDS);
    Card c (Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(a.is_left_bower(trump));
    ASSERT_TRUE(b.is_left_bower(trump));
    ASSERT_FALSE(c.is_left_bower(trump));
}

//bool operators test 
TEST(test_operator_less){
    Card h = {Card::RANK_ACE,Card::SUIT_DIAMONDS};//highest valued
    Card l; //lowest valued
    Card a = {Card::RANK_TEN,Card::SUIT_HEARTS};//base case 1
    Card b = {Card::RANK_JACK,Card::SUIT_CLUBS};//base case 2
    Card c = {Card::RANK_TEN,Card::SUIT_CLUBS};//tie for case 1
    Card d = {Card::RANK_TEN,Card::SUIT_SPADES};//tie for case 1 
    ASSERT_FALSE(h<a); 
    ASSERT_FALSE(a<a);
    ASSERT_TRUE(l<a);
    ASSERT_TRUE(l<h);
    ASSERT_TRUE(a<b);
    ASSERT_TRUE(a<c);
    ASSERT_FALSE(a<d);
}

TEST(test_operator_less_or_equal){
    Card h = {Card::RANK_ACE,Card::SUIT_DIAMONDS};//highest valued
    Card l; //lowest valued
    Card a = {Card::RANK_TEN,Card::SUIT_HEARTS};//base case 1
    Card b = {Card::RANK_JACK,Card::SUIT_CLUBS};//base case 2
    Card c = {Card::RANK_TEN,Card::SUIT_CLUBS};//tie for case 1
    Card d = {Card::RANK_TEN,Card::SUIT_SPADES};//tie for case 1 
    ASSERT_FALSE(h<=a); 
    ASSERT_TRUE(h<=h);
    ASSERT_TRUE(a<=a);
    ASSERT_TRUE(l<=a);
    ASSERT_TRUE(l<=h);
    ASSERT_TRUE(a<=b);
    ASSERT_TRUE(a<=c);
    ASSERT_FALSE(a<=d);
}

TEST(test_operator_greater){
    Card h = {Card::RANK_ACE,Card::SUIT_DIAMONDS};//highest valued
    Card l; //lowest valued
    Card a = {Card::RANK_TEN,Card::SUIT_HEARTS};//base case 1
    Card b = {Card::RANK_JACK,Card::SUIT_CLUBS};//base case 2
    Card c = {Card::RANK_TEN,Card::SUIT_CLUBS};//tie for case 1
    Card d = {Card::RANK_TEN,Card::SUIT_SPADES};//tie for case 1 
    ASSERT_TRUE(h>a);
    ASSERT_FALSE(l>a);
    ASSERT_FALSE(a>a);
    ASSERT_TRUE(b>a);
    ASSERT_TRUE(c>a);
    ASSERT_FALSE(d>a);
}

TEST(test_operator_greater_or_equal){
    Card h = {Card::RANK_ACE,Card::SUIT_DIAMONDS};//highest valued
    Card l; //lowest valued
    Card a = {Card::RANK_TEN,Card::SUIT_HEARTS};//base case 1
    Card b = {Card::RANK_JACK,Card::SUIT_CLUBS};//base case 2
    Card c = {Card::RANK_TEN,Card::SUIT_CLUBS};//tie for case 1
    Card d = {Card::RANK_TEN,Card::SUIT_SPADES};//tie for case 1 
    ASSERT_TRUE(h>=a);
    ASSERT_FALSE(l>=a);
    ASSERT_TRUE(l>=l);
    ASSERT_TRUE(a>=a);
    ASSERT_TRUE(b>=a);
    ASSERT_TRUE(c>=a);
    ASSERT_FALSE(d>=a);
}

TEST(test_operator_equal){
    Card a(Card::RANK_ACE,Card::SUIT_CLUBS);
    Card b(Card::RANK_KING,Card::SUIT_DIAMONDS);
    ASSERT_TRUE(a==a);
    ASSERT_TRUE(b==b);
    ASSERT_FALSE(b==a);
}

TEST(test_operator_not_equal){
    Card a(Card::RANK_ACE,Card::SUIT_CLUBS);
    Card b(Card::RANK_KING,Card::SUIT_DIAMONDS);
    ASSERT_TRUE(a!=b);
    ASSERT_FALSE(a!=a);
    ASSERT_FALSE(b!=b);
}

///non-bool operators
TEST(test_is_next){
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS),Card::SUIT_SPADES); 
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES),Card::SUIT_CLUBS); 
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS),Card::SUIT_DIAMONDS); 
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS),Card::SUIT_HEARTS); 
}

TEST(test_cout_operator){
    Card a(Card::RANK_ACE,Card::SUIT_CLUBS);
    Card b(Card::RANK_KING,Card::SUIT_DIAMONDS);
    ostringstream output_a_actual, output_a;
    ostringstream output_b_actual, output_b; 
    output_a_actual << "Ace of Clubs";
    output_b_actual << "King of Diamonds";
    output_a << a; 
    output_b << b;
    ASSERT_EQUAL(output_a_actual.str(),output_a.str());
    ASSERT_EQUAL(output_b_actual.str(),output_b.str());
}

//trump suit cases

TEST(test_card_less_heart){
    string trump = Card::SUIT_HEARTS;
    Card right_bower = {Card::RANK_JACK,Card::SUIT_HEARTS};
    Card left_bower = {Card::RANK_JACK,Card::SUIT_DIAMONDS};

    //trump cards
    Card trump_one = {Card::RANK_ACE,Card::SUIT_HEARTS};
    Card trump_two = {Card::RANK_QUEEN,Card::SUIT_HEARTS};
    ;
    
    //testing right vs left bower
    ASSERT_TRUE(Card_less(left_bower,right_bower,trump));

    //testing right and left bower with other trumps
    ASSERT_TRUE(Card_less(trump_one,right_bower,trump));
    ASSERT_TRUE(Card_less(trump_two,right_bower,trump));
    ASSERT_TRUE(Card_less(trump_one,left_bower,trump));
    ASSERT_TRUE(Card_less(trump_two,left_bower,trump));

}

TEST(test_card_less_spade){
    string trump = Card::SUIT_SPADES;
    Card right_bower = {Card::RANK_JACK,trump};

    //trump cards
    Card trump_one = {Card::RANK_ACE,trump};
    Card trump_two = {Card::RANK_KING,trump};
    Card trump_three = {Card::RANK_TWO,trump};

    //normal cards
    Card h = {Card::RANK_ACE,Card::SUIT_DIAMONDS};//highest valued
    Card l = {Card::RANK_TWO,Card::SUIT_HEARTS}; //lowest valued
    Card a = {Card::RANK_TEN,Card::SUIT_DIAMONDS};//base case 1
    Card c = {Card::RANK_TEN,Card::SUIT_CLUBS};//tie for case 1

    //testing trumps with normal suits 
    ASSERT_TRUE(Card_less(h,right_bower,trump));
    ASSERT_TRUE(Card_less(h,trump_one,trump));
    ASSERT_TRUE(Card_less(a,trump_two,trump));
    ASSERT_TRUE(Card_less(c,trump_three,trump));

}

TEST(test_card_less_diamonds){
    string trump = Card::SUIT_DIAMONDS;
    Card right_bower = {Card::RANK_JACK,trump};
    Card left_bower = {Card::RANK_JACK,Suit_next(trump)};
    
    //trump cards
    Card trump_one = {Card::RANK_ACE,trump};
    Card trump_two = {Card::RANK_KING,trump};
    Card trump_three = {Card::RANK_QUEEN,trump};
    Card trump_four = {Card::RANK_TEN,trump};

    ASSERT_TRUE(Card_less(trump_two,trump_one,trump));
    ASSERT_TRUE(Card_less(trump_three,trump_two,trump));
    ASSERT_TRUE(Card_less(trump_four,trump_three,trump));
    ASSERT_TRUE(Card_less(trump_four,trump_one,trump));

    //left vs right bower
    ASSERT_TRUE(Card_less(left_bower,right_bower,trump));

    //testing right and left bower with other trumps
    ASSERT_TRUE(Card_less(trump_one,right_bower,trump));
    ASSERT_TRUE(Card_less(trump_two,right_bower,trump));
    ASSERT_TRUE(Card_less(trump_one,left_bower,trump));
    ASSERT_TRUE(Card_less(trump_two,left_bower,trump));

}

// led suit cases

TEST(test_card_less_trump_led_equal_heart){
    string trump = Card::SUIT_HEARTS;
    Card led = {Card::RANK_KING,trump};
    Card right_bower = {Card::RANK_JACK,trump};
    Card left_bower = {Card::RANK_JACK,Suit_next(trump)};

    //trump cards
    Card trump_one = {Card::RANK_ACE,trump};
    Card trump_two = {Card::RANK_QUEEN,trump};
    Card trump_three = {Card::RANK_TWO,trump};
    Card trump_four = {Card::RANK_SEVEN,trump};
 

    //normal cards
    Card h = {Card::RANK_ACE,Card::SUIT_DIAMONDS};//highest valued
    Card l; //lowest valued
    Card a = {Card::RANK_TEN,Card::SUIT_DIAMONDS};//base case 1
    Card b = {Card::RANK_JACK,Card::SUIT_CLUBS};//base case 2
    Card c = {Card::RANK_TEN,Card::SUIT_CLUBS};//tie for case 1
    Card d = {Card::RANK_TEN,Card::SUIT_SPADES};//tie for case 1 
    
    //testing right vs left bower
    ASSERT_TRUE(Card_less(left_bower,right_bower,led,trump));

    //testing right and left bower with other trumps
    ASSERT_TRUE(Card_less(trump_one,right_bower,led,trump));
    ASSERT_TRUE(Card_less(trump_two,right_bower,led,trump));
    ASSERT_TRUE(Card_less(trump_one,left_bower,led,trump));
    ASSERT_TRUE(Card_less(trump_two,left_bower,led,trump));

    //testing in between trumps
    ASSERT_TRUE(Card_less(trump_four,trump_one,led,trump));
    ASSERT_TRUE(Card_less(trump_two,trump_one,led,trump));
    ASSERT_TRUE(Card_less(trump_three,trump_two,led,trump));
    ASSERT_TRUE(Card_less(trump_three,trump_four,led,trump));

    //testing trumps with normal suits 
    ASSERT_TRUE(Card_less(h,right_bower,led,trump));
    ASSERT_TRUE(Card_less(h,trump_one,led,trump));
    ASSERT_TRUE(Card_less(a,trump_two,led,trump));
    ASSERT_TRUE(Card_less(c,trump_three,led,trump));

    //normal suits ~ highest + lowest
    ASSERT_TRUE(Card_less(a,h,led,trump));
    ASSERT_TRUE(Card_less(b,h,led,trump));
    ASSERT_TRUE(Card_less(l,h,led,trump));
    ASSERT_TRUE(Card_less(l,c,led,trump));
    ASSERT_TRUE(Card_less(l,d,led,trump));

    //normal suits
    ASSERT_TRUE(Card_less(c,a,led,trump));
    ASSERT_TRUE(Card_less(d,a,led,trump));
    ASSERT_TRUE(Card_less(d,c,led,trump));
    ASSERT_TRUE(Card_less(a,b,led,trump));
    ASSERT_TRUE(Card_less(c,b,led,trump));
}

TEST(test_card_less_trump_heart_led_spade){
    string trump = Card::SUIT_HEARTS; 
    string led_suit = Card::SUIT_SPADES; 
    Card led = {Card::RANK_THREE,led_suit};

    //bowers
    Card right_bower = {Card::RANK_JACK,trump};
    Card left_bower = {Card::RANK_JACK,Suit_next(trump)};

    //trump cards
    Card trump_one = {Card::RANK_ACE,trump};

    //led cards
    Card led_one = {Card::RANK_ACE,led_suit};
    Card led_two = {Card::RANK_KING,led_suit};
    Card led_three = {Card::RANK_JACK,led_suit};
    Card led_four = {Card::RANK_SEVEN,led_suit};

    //led vs trumps 
    ASSERT_TRUE(Card_less(led_four,trump_one,led,trump));

    //in between led
    ASSERT_TRUE(Card_less(led_two,led_one,led,trump));
    ASSERT_TRUE(Card_less(led_three,led_two,led,trump));

}

// Add more test cases here

TEST_MAIN()
