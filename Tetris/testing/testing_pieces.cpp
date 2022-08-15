#include "ttrs_pieces.h"
#include <iostream>
#define BLOCK_SIZE 5

int main(){
    srand((unsigned int)time(NULL));
    Piece  piece_test;
    Piece  piece_test_o; 

    piece_test.print_piece();
    piece_test_o.print_piece();

}