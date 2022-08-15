// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<double> > summarize(vector<double> v) {
  assert(!v.empty());
  vector<vector<double> > summarize;
  vector<double> entry;
  v.push_back(v[v.size()-1]+1);

  double holder = v[0];
  int count = 0;
  for(int i =0;i<static_cast<int>(v.size());i++){
    if(holder!=v[i]){
      entry = {holder,static_cast<double>(i-count)};
      summarize.push_back(entry);
      holder = v[i];
      count = i;
    }
  }
  return summarize;

}

int count(vector<double> v) {
  return v.size();
}
double sum(vector<double> v) {
  assert(!v.empty());
  double sum = 0; 
  for(size_t i=0;i<v.size();i++){
    sum += v[i];
  }
  return sum;
}
double mean(vector<double> v) {
  assert(!v.empty());
  return sum(v)/count(v); 
}

double median(vector<double> v) {
  assert(!v.empty());
  if(v.size()%2==1){
    return v[(v.size()-1)/2];
  }
  else{
    return (v[(v.size()/2)-1]+v[(v.size())/2])/2;
  }
}
double mode(vector<double> v) {
  assert(!v.empty()); 
  int max = 0;
  int max_index=0; 

  for(int i=0;i<static_cast<int>(v.size());i++){
    double holder = v[i];
    int count = 0;
    for(int j=0;j<static_cast<int>(v.size());j++){
      if(holder==v[j]){
        count++; 
      }
    }
    if(count>max){
      max = count;
      max_index = i;
    }
  }
  return v[max_index];   
}
double min(vector<double> v) {
  assert(!v.empty());
  return v[0];
}
double max(vector<double> v) {
  assert(!v.empty());
  return v[v.size()-1];
}
double stdev(vector<double> v) {
  assert(v.size()>1);
  double count = 0;

  for(size_t i=0;i<v.size();i++){
    count+=pow((v[i] - mean(v)),2);
  }

  count = sqrt(count/(v.size()-1));
  return count; 
}
//done

double percentile(vector<double> v, double p) {
  assert(!v.empty());
  assert(p<=1 && p>=0);
  double n = p*(v.size()-1)+1;
  
  double intpart,fractpart;
  fractpart = modf(n,&intpart);
  intpart--; 

  double percentile;
  if(v.size()==1 || p==1){
    percentile = v[intpart];
  }
  else{
    percentile = v[intpart] + fractpart*(v[intpart+1]-v[intpart]);
  }
  return percentile;
}