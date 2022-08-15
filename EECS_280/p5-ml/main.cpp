// Project UID db1f506d06d84ab787baf250c265e24e
#include "csvstream.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cmath> 
#include <map>

using namespace std; 

bool error_checking(int argc, char *const argv[]);
bool file_checking(string train_file, string test_file);

class train_interface{
    private:
    bool debug = false; int num_posts = 0; int vocab_size; 
    map<string,int> train_words_map;
    map<string,int> train_tag_map;
    map<pair<string,string>,int> train_tag_words_map;

    set<string> unique_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;
        // Read word by word from the stringstream and insert into the set
        while (source >> word) {
            words.insert(word);
        }
        return words;
    }

    void map_init(string &tag,set<string> &holder){
        train_tag_map[tag]++;
        for(auto &item:holder){
            train_words_map[item]++;
            train_tag_words_map[{tag,item}]++; 
        }
    }

    void print_training_class_debug(){
            cout << "classes:" << endl;
            map<string,int>::iterator itr = train_tag_map.begin();
            for(;itr!=train_tag_map.end();++itr){
                cout << "  " << itr->first <<", "<<itr->second <<
                " examples, log-prior = " << log(double((itr->second))/num_posts) << endl;
            }
            cout << "classifier parameters:" << endl;
            map<pair<string,string>,int>::iterator itr_tag_map = 
            train_tag_words_map.begin();
            for(;itr_tag_map!=train_tag_words_map.end();++itr_tag_map){
                pair<string,string> holder = itr_tag_map->first;
                cout << "  " << holder.first <<":"<< holder.second <<", count = "<<
                itr_tag_map->second << ", log-likelihood = " << 
                log(double((itr_tag_map->second))/train_tag_map[holder.first]) 
                << endl;
            }
    }
    
    public:

    train_interface(){}

    train_interface(string train_file_in, int argc){
        csvstream train_file(train_file_in);
        if(argc==4){debug = true; cout << "training data:" << endl;}
        map<string,string> row; 
        set<string> static holder; static string line; 
        while(train_file >> row){
            for(auto &col:row){
                if(col.first=="content"){
                    num_posts++; 
                    line = col.second; 
                    holder = unique_words(col.second);
                }
                if(col.first=="tag"){ 
                    map_init(col.second,holder);
                    if(debug){
                        cout << "  label = "<< col.second << 
                        ", content = " << line << endl;
                    }
                }
            }
        }
        vocab_size = train_words_map.size();
    }
    
    void print_training_data(){
            cout << "trained on " << num_posts <<" examples" << endl;
            //missing vocab size 
            if(debug){
                cout << "vocabulary size = " << vocab_size << endl;
                cout << endl;
                print_training_class_debug();
            }
            cout << endl;
        }

    map<string,int>& get_words_map(){
        return train_words_map; 
    }      

    map<string,int>& get_tag_map(){
        return train_tag_map; 
    }

    map<pair<string,string>,int>& get_tag_words_map(){
        return train_tag_words_map; 
    }

    void print_map(map<string,int> &map_in){
        map<string,int>::iterator itr = map_in.begin();
        for(;itr!=map_in.end();++itr){
            pair<string,int> holder = *itr;
            cout << holder.first << " " << holder.second << endl;
        }
    }

    void print_map(map<pair<string,string>,int> &map_in){
        map<pair<string,string>,int>::iterator itr = map_in.begin();
        for(;itr!=map_in.end();++itr){
            pair<pair<string,string>,int> holder = *itr;
            pair<string,string> holder_copy = holder.first;
            cout << holder_copy.first << " " << holder_copy.second << 
            " "<< holder.second <<endl;
        }
    }

    int n_training_post(){
        return num_posts; 
    }

};

class file_interface{
    private:
    train_interface train_file;
    csvstream file_csv; 
    vector<pair<string,double>> result_holder; 
    int num_training_posts = 0;
    int num_posts = 0; 

    set<string> unique_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;
        // Read word by word from the stringstream and insert into the set
        while (source >> word) {
            words.insert(word);
        }
        return words;
    }
    
    void calculating_log_by_line(string line){
        result_holder.clear();
        map<string,int>::iterator tag_itr = 
        train_file.get_tag_map().begin();
        set<string> set_string = unique_words(line); 
        for(;tag_itr!=train_file.get_tag_map().end();++tag_itr){
            double log_sum = 0;
            log_sum += log(tag_itr->second/double(num_training_posts));
            for(auto &item : set_string){
                int tag_word_count = 
                train_file.get_tag_words_map()[{tag_itr->first,item}];
                int tag_count = train_file.get_tag_map()[tag_itr->first];
                int word_count = train_file.get_words_map()[item]; 
                if(word_count == 0){
                    log_sum += log(1/double(num_training_posts));
                }
                else if(word_count!=0 && tag_word_count ==0){
                    log_sum += log(word_count/double(num_training_posts));
                }
                else if (tag_word_count!=0){
                    log_sum += log(tag_word_count/double(tag_count));
                }
            }
            result_holder.push_back({tag_itr->first,log_sum});
        }
    }

    void finding_max_tag_and_value(double &max_value,string &max_tag){
        max_value = result_holder[0].second; 
        max_tag = result_holder[0].first;
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
    }

    public:

    file_interface(string train_file_in, string file_in,int argc): 
    train_file(train_file_in,argc),file_csv(file_in){
        train_file.print_training_data();
        num_training_posts = train_file.n_training_post();

    }

    void calculating_log(){
        map<string,string> row; static string line; 
        int correct_counter = 0;
        cout << "test data:" << endl;
        while(file_csv >> row){
            for(auto& item:row){
                if(item.first=="tag"){
                    string max_tag; double max_value;  
                    calculating_log_by_line(line);
                    finding_max_tag_and_value(max_value,max_tag); 
                    cout << "  correct = " << item.second << ", predicted = " << max_tag 
                    << ", log-probability score = " << max_value << endl; 
                    cout << "  content = " << line << endl; cout << endl;
                    if(item.second==max_tag){correct_counter++;}

                }
                if(item.first=="content"){
                    num_posts++; 
                    line = item.second;
                }
            }
        }
        cout << "performance: " << correct_counter << 
        " / " << num_posts << " posts predicted correctly" << endl;
    }

};

int main(int argc, char * argv[]){
    cout.precision(3);
    if(!error_checking(argc,argv) || !file_checking(argv[1],argv[2])){
        return 1;
    }
    file_interface file(argv[1],argv[2],argc);
    file.calculating_log();
}

bool file_checking(string train_file, string test_file){
    ifstream fin_train, fin_test; 
    fin_train.open(train_file); fin_test.open(test_file);
    if(!fin_test.is_open()){
        cout << "Error opening file: " << test_file << endl;
        return false;
    }
    if(!fin_train.is_open()){
        cout << "Error opening file: " << train_file << endl;
        return false;
    }
    return true;
}

bool error_checking(int argc, char *const argv[]){

    if(!(argc==3 || argc ==4)){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return false; 
    }
    if(argc==4){
        string debug = argv[3];
        if(debug!="--debug"){
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return false;
        }
    }

    return true; 
}
