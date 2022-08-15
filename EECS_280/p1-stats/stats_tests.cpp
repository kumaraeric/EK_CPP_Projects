/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

void test_sum_small_data_set();
void test_count_small_data_set();
void test_mean_small_data_set();
void test_min_small_data_set();
void test_max_small_data_set();
void test_mode_small_data_set();
void test_median_small_data_set();
void test_stdev_small_data_set();
void test_percentile_small_data_set();
void test_summarize_small_data_set();

// Add prototypes for you test functions here.

int main() {
  test_sum_small_data_set();
  test_count_small_data_set();
  test_mean_small_data_set();
  test_min_small_data_set();
  test_max_small_data_set();
  test_median_small_data_set();
  test_mean_small_data_set();
  test_percentile_small_data_set();
  test_stdev_small_data_set();
  test_summarize_small_data_set();
  // Call your test functions here
  return 0;
}

void test_summarize_small_data_set(){
  cout << "test_summarize_small_data_set" << endl;
  vector <double> data = {1,1,2,3,3}; 
  vector <vector<double>> comparison = {{1,2},{2,1},{3,2}};
  assert(summarize(data)==comparison);
  cout << "PASS" << endl;
}

void test_stdev_small_data_set(){
  cout << "test_stdev_small_data_set" << endl; 
  vector<double> data; 
  data.push_back(6);
  data.push_back(7);
  data.push_back(8);
  data.push_back(9);
  data.push_back(10);
  assert((stdev(data)-1.58114) < 0.0001);
  cout << "PASS" << endl;
}

void test_percentile_small_data_set(){
  cout << "test_percentile_small_data_set" << endl; 
  vector<double> data; 
  data.push_back(15);
  data.push_back(20);
  data.push_back(35);
  data.push_back(40);
  data.push_back(50);
  double p = 0.4; 
  assert(percentile(data,p)==29);
  cout << "PASS" << endl;
}

void test_mode_small_data_set(){
  cout << "test_mode_small_data_set" << endl;

  vector<double> data;

  data.push_back(1);
  data.push_back(1);
  data.push_back(2);
  data.push_back(2);

  vector<double> data2; 
  data2.push_back(1);

  assert(mode(data2)==1);
  assert(mode(data) == 1);

  data.push_back(2); 
  assert(mode(data)==2); 

  data.push_back(1);
  data.push_back(1);
  data.push_back(3);
  assert(mode(data)==1);

  cout << "PASS!" << endl;
}
void test_median_small_data_set(){
  cout << "test_median_small_data_set" << endl;

  vector<double> data;

  data.push_back(0);
  data.push_back(1);
  data.push_back(2);
  data.push_back(2);

  vector<double> data2; 
  data2.push_back(1);
  data2.push_back(2);
  data2.push_back(3);

  assert(median(data2)==2);
  assert(median(data) == 1.5);


  cout << "PASS!" << endl;
}

void test_max_small_data_set() {
  cout << "test_max_small_data_set" << endl;

  vector<double> data;

  data.push_back(0);
  data.push_back(1);
  data.push_back(2);
  data.push_back(2);

  vector<double> data2; 
  data2.push_back(1);

  assert(max(data2)==1);
  assert(max(data) == 2);

  cout << "PASS!" << endl;
}

void test_min_small_data_set() {
  cout << "test_min_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  vector<double> data2; 
  data2.push_back(1);

  assert(min(data2)==1);
  assert(min(data) == 1);

  cout << "PASS!" << endl;
}

void test_mean_small_data_set(){
   cout << "test_mean_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  vector<double> data2; 
  data2.push_back(1);

  assert(mean(data2)==1);
  assert(mean(data)==2);

  cout << "PASS" << endl;

}

void test_count_small_data_set(){
   cout << "test_count_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  vector<double> data2; 
  data2.push_back(1);

  assert(count(data2)==1);
  assert(count(data)==3);
  

  cout << "PASS" << endl;

}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  vector<double> data2; 
  data2.push_back(1);

  assert(sum(data) == 6);
  assert(sum(data2)==1);


  cout << "PASS!" << endl;
}

// Add the test function implementations here.
