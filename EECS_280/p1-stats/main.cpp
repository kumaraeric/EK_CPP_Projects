// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
// hello
#include "stats.h"
#include "p1_library.h"
#include <iostream>
using namespace std;
int main() {
  string filename, column_name;
  cout << "enter a filename" << endl; 
  cin >> filename;
  cout << "enter a column name" << endl;
  cin >> column_name;
  cout << "reading column " << column_name <<" from " << filename << endl;

  vector<double> data = extract_column(filename,column_name); 
  sort(data);

  //printing summary
  cout << "Summary (value: frequency)" << endl;
  vector<vector<double>> summary = summarize(data); 
  for(size_t i =0;i<summary.size();i++){
    cout << summary[i][0]<<": "<<summary[i][1]<< endl; 
  }
  cout << endl;
  
  //printing statistics - excluding percentile
  cout << "count = " << count(data) <<endl;
  cout << "sum = " << sum(data) <<endl;
  cout << "mean = " << mean(data) <<endl;
  cout << "stdev = " << stdev(data) <<endl;
  cout << "median = " << median(data) <<endl;
  cout << "mode = " << mode(data) <<endl;
  cout << "min = " << min(data) <<endl;
  cout << "max = " << max(data) <<endl;

  //printing percentile
  string space;
  for(int i =0;i<5;i++){
    if(i==0){
      space="  ";
    }
    else if(i<4&&i>0){
      space=" ";
    }
    else{
      space="";
    }

    cout<<space<<i*25<<"th percentile = "<<percentile(data,i*0.25)<<endl;
  }


}