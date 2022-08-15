#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
  ifstream is;
  is.open("dog.ppm"); 
  int counter; 
  string line;
  string total = "";
  while(getline(is,line)){
    total = total + line +"\n";
    counter++;
  }
  cout << total.pop_back() << endl;

}