#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main(){
    vector<pair<string,double>> result_holder;
    result_holder.push_back({"eucher",-1.1});
    result_holder.push_back({"calculator",-1.1});
    result_holder.push_back({"statistics",-4.1});

    double max_value = result_holder[0].second; 
    string max_tag = result_holder[0].first;
    for(int j = 1;j<int(result_holder.size());++j){
        if(result_holder[j].second > max_value){
            max_value = result_holder[j].second; 
            max_tag = result_holder[j].first; 
        }
        if(result_holder[j].second == max_value 
        && less<string>{}(result_holder[j].first,max_tag)){
            max_tag = result_holder[j].first; 
        }
    }

    cout << "max value - max_tag" << endl;
    cout << max_value << "-" << max_tag << endl;

}




