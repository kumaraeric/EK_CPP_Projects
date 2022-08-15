// Project UID af1f95f547e44c8ea88730dfb185559d
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Image.h"
#include "processing.h"
using namespace std;

int main(int argc, char *argv[]){

    if(argc < 4 || argc > 5){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }

    string filename_in = argv[1];
    string filename_out = argv[2];
    Image *img = new Image;

    ifstream fin;
    fin.open(filename_in.c_str());
    if (!fin.is_open()){
    cout << "Error opening file: " << filename_in << endl;
    return 1;
    }

    Image_init(img,fin);
    int new_width = atoi(argv[3]);
    int new_height = Image_height(img);
    if(argc==5){
        new_height= atoi(argv[4]);
    }
        //error checking
    if(!(new_height > 0 && new_height <= Image_height(img))){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }
        if(!(new_width > 0 && new_width <= Image_width(img))){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
        }
    
    seam_carve(img,new_width,new_height);

    ofstream fout;
    fout.open(filename_out.c_str());
    Image_print(img,fout);
    delete img; 
    
}
