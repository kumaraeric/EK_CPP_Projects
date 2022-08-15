#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class Character {
private:
  string name;

public:
  Character(const string &name_in)
   : name(name_in) {
    cout << "Character ctor" << endl;
  }

  const string & get_name() const {
    return name;
  }

  void describe() const {
    cout << "Character: " << get_name() << endl;
  }

  virtual void introduce() const {
    cout << "A generic character" << endl;
  }
};

class Hero : public Character {
private:
  string kingdom;

public:
  Hero(const string &name_in, const string &kingdom_in)
   : Character(name_in), kingdom(kingdom_in) {
    cout << "Hero ctor" << endl;
  }

  const string & get_kingdom() const {
    return kingdom;
  }

  void describe() const {
    cout << "Hero: " << get_name() << endl;
  }

  virtual void introduce() const override {
    cout << "I hail from " << kingdom << endl;
  }
};

class Knight : public Hero {
public:
  Knight(const string &name_in, const string & kingdom_in)
   : Hero(name_in, kingdom_in) {
    cout << "Knight ctor" << endl;
  }

  void describe() const {
    cout << "Knight: " << get_name() << endl;
  };
};

int main(int argc, char* argv[]){

    Character character("Alexandra");
    Knight knight("Alexandra","Greece");
    character.introduce();
    Hero *c_ptr = &knight;
    c_ptr->introduce();
    //    if(argc!=2){
//   cout << "invalid args" << endl;
//   return 1;
// }

// string filename = argv[1];
// ofstream fout;
// fout.open(filename);
// // if(!fout.is_open()){
//   cout << "output stream error" << endl;
// 	return 1;
// }

// string word_in = "";
// string word;
// while(word_in!="STOP"){
//   cin >> word_in;
//   if(word_in!= "STOP"){
//     word = word_in + "wow";
//     fout << word << endl;
//   }

}

