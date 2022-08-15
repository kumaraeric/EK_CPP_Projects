// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
#include "unit_test_framework.h"

using std::pair;
using std::string;
using std::vector;

TEST(test_operator){
  Map<string,int> test;
  test.insert({"ae",10});
  ASSERT_EQUAL(test["ae"],10);
  test["ae"] = 1000;
  pair<string,int> test_v = {"ae",1000};
  ASSERT_EQUAL(*test.find("ae"),test_v);
  ASSERT_EQUAL(test.find("aa"),test.end());
  test["aa"];
  pair<string,int> test_v_2 = {"aa",0};
  ASSERT_EQUAL(*test.find("aa"),test_v_2);
  test["aa"] = 5000;
  test_v_2 = {"aa",5000};
  ASSERT_EQUAL(*test.find("aa"),test_v_2);

}

TEST(test_insert){
  Map<string,int> test;
  pair<Map<string,int>::Iterator,bool> val_1 = test.insert({"ae",10});
  pair<Map<string,int>::Iterator,bool> val_2 = test.insert({"ad",10});
  pair<Map<string,int>::Iterator,bool> val_3 = test.insert({"ae",10});

  pair<Map<string,int>::Iterator,bool> cor_1 = {++test.begin(),true};
  pair<Map<string,int>::Iterator,bool> cor_2 = {test.begin(),true};
  pair<Map<string,int>::Iterator,bool> cor_3 = {++test.begin(),false};

  ASSERT_EQUAL(val_1,cor_1);
  ASSERT_EQUAL(val_2,cor_2);
  ASSERT_EQUAL(val_3,cor_3);

}

TEST(test_find){
  Map<string,int> test;
  test.insert({"ae",10});
  test.insert({"ac",1});
  test.insert({"al",100});
  test.insert({"ad",-1});
  test.insert({"ah",200});
  test.insert({"az",1000});  
  pair<string,int> test_v = {"ad",-1};
  ASSERT_EQUAL(test.find("aa"),test.end());
  ASSERT_EQUAL(*test.find("ad"),test_v);
}

TEST(test_back_end){
  Map<string,int> test;
  test.insert({"ae",10});
  test.insert({"ac",1});
  test.insert({"al",100});
  test.insert({"ad",-1});
  test.insert({"ah",200});
  test.insert({"az",1000});
  pair<string,int> test_v = {"ac",1};
  Map<string,int>::Iterator itr;
  ASSERT_EQUAL(*test.begin(),test_v);
  ASSERT_EQUAL(test.end(),itr);
}

TEST(test_size_empty){
  Map<string,int> test;
  ASSERT_TRUE(test.empty())
  ASSERT_EQUAL(test.size(),0u)
  test.insert({"wow",1});
  test.insert({"oow",2});
  ASSERT_FALSE(test.empty())
  ASSERT_EQUAL(test.size(),2u)
}

TEST(map_copy_ctr){
  Map<string,int> test;
  test.insert({"wow",1});
  test.insert({"oow",2});
  Map<string,int> test_copy(test);

  Map<string,int>::Iterator itr = test.begin();
  Map<string,int>::Iterator itr_copy = test_copy.begin();

  for(;itr!=test.end();itr++){
    ASSERT_NOT_EQUAL(itr,itr_copy);
    ASSERT_EQUAL(*itr,*itr_copy);
    itr_copy++;
  }
}

TEST(map_copy_assignment){
  Map<string,int> test;
  test.insert({"wow",1});
  test.insert({"oow",2});
  Map<string,int> test_copy = test; 
  Map<string,int>::Iterator itr = test.begin();
  Map<string,int>::Iterator itr_copy = test_copy.begin();

  for(;itr!=test.end();itr++){
    ASSERT_NOT_EQUAL(itr,itr_copy);
    ASSERT_EQUAL(*itr,*itr_copy);
    itr_copy++;
  }
}

TEST(map_default_ctr){
  Map<string,int> test;
  ASSERT_TRUE(test.empty());
  ASSERT_EQUAL(test.size(),0);
}

TEST(map_public_test) {
  // A map stores two types, key and value
  Map<string, double> words;

  // One way to use a map is like an array
  words["hello"] = 1;
  ASSERT_EQUAL(words["hello"], 1);

  // Maps store a std::pair type, which "glues" one key to one value.
  // The CS term is Tuple, a fixed-size heterogeneous container.
  pair<string, double> tuple;
  tuple.first = "world";
  tuple.second = 2;
  words.insert(tuple);
  ASSERT_EQUAL(words["world"], 2);

  // Here's the C++11 way to insert a pair
  words.insert({"pi", 3.14159});
  ASSERT_ALMOST_EQUAL(words["pi"], 3.14159, 0.00001);

  vector<string> expected_keys = { "hello", "pi", "world" };
  vector<double> expected_values = { 1, 3.14159, 2 };
  vector<string> actual_keys;
  vector<double> actual_values;
  // Iterate over map contents using a C++11 range-for loop
  // This is the equivalent without C++11:
  // for (Map<string, double>::Iterator it = words.begin();
  //      it != words.end(); ++it) {
  //   pair<string, double> &p = *it;
  for (auto &p : words) {
    auto word = p.first; //key
    auto number = p.second; //value
    actual_keys.push_back(word);
    actual_values.push_back(number);
  }
  ASSERT_EQUAL(expected_keys, actual_keys);
  ASSERT_EQUAL(expected_values, actual_values);

  // Check if a key is in the map.  find() returns an iterator.
  auto found_it = words.find("pi");
  ASSERT_NOT_EQUAL(found_it, words.end());
  auto &word = (*found_it).first; //key
  auto number = (*found_it).second; //value
  ASSERT_EQUAL(word, "pi");
  ASSERT_ALMOST_EQUAL(number, 3.14159, 0.00001);

  // When using the [] notation. An element not found is automatically created.
  // If the value type of the map is numeric, it will always be 0 "by default".
  ASSERT_EQUAL(words["bleh"], 0.0);
}

TEST_MAIN()
