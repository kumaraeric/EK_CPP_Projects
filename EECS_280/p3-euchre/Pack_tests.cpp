// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"
#include <fstream>
#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());

    Card seconds = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, seconds.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, seconds.get_suit());
}

TEST(test_deal_edge_case_empty_reset){
    Pack pack; 
    for(int i =0;i<23;++i){
        pack.deal_one(); 
    }

    Card last = pack.deal_one(); 
    ASSERT_EQUAL(Card::RANK_ACE,last.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS,last.get_suit());

    ASSERT_TRUE(pack.empty())

    pack.reset();

    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

TEST(test_reading_from_file){
    ifstream fin("pack_test_2");
    Pack pack(fin);

    for(int i=0;i<8;++i){
        Card first = pack.deal_one();
        ASSERT_EQUAL(Card::RANK_JACK, first.get_rank());
        ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());

        Card second = pack.deal_one();
        ASSERT_EQUAL(Card::RANK_JACK, second.get_rank());
        ASSERT_EQUAL(Card::SUIT_DIAMONDS, second.get_suit());

        Card third = pack.deal_one();
        ASSERT_EQUAL(Card::RANK_QUEEN, third.get_rank());
        ASSERT_EQUAL(Card::SUIT_DIAMONDS, third.get_suit());
    }
    
    ASSERT_TRUE(pack.empty());
}

TEST(test_shuffle){
    ifstream fin("pack.in");
    Pack pack(fin);
    pack.shuffle();
    ostringstream out; 
    for(int i =0;i<8;++i){
        Card holder = pack.deal_one();
        out << holder << endl;
    }

    ostringstream actual; 
    actual << Card{Card::RANK_KING, Card::SUIT_CLUBS}<< endl
    << Card{Card::RANK_JACK, Card::SUIT_HEARTS}<< endl
    << Card{Card::RANK_NINE, Card::SUIT_SPADES}<< endl
    << Card{Card::RANK_ACE, Card::SUIT_CLUBS}<< endl
    << Card{Card::RANK_QUEEN, Card::SUIT_HEARTS}<< endl
    << Card{Card::RANK_TEN, Card::SUIT_SPADES}<< endl
    << Card{Card::RANK_NINE, Card::SUIT_DIAMONDS}<< endl
    << Card{Card::RANK_KING, Card::SUIT_HEARTS}<< endl;

    ASSERT_EQUAL(actual.str(),out.str());
        
}

// Add more tests here

TEST_MAIN()
