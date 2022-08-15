#include "ttrs_pieces.h"
#include "ttrs_board.h"

#include <iostream>
using namespace std;

int main(){
    
    srand((unsigned int)time(NULL));
    Board curr_board;
    curr_board.get_board_value(0,0) = 1;
    for(int j = 0; j < BOARD_WIDTH; ++j){
        curr_board.get_board_value(10,j) = 1;
    }
    curr_board.get_board_value(18,1) = 1;
    curr_board.print_board(16,1);
    cout << curr_board.auto_case(16,1) << endl;
    curr_board.new_piece();
    curr_board.print_board(10,5);

    // for(int j = 0; j < BOARD_WIDTH; ++j){
    //     curr_board.get_board_value(10,j) = 1;
    //     curr_board.get_board_value(9,j) = 1;
    // }

    // curr_board.get_board_value(8,1) = 1;
    // curr_board.print_board(10,5);
    // curr_board.delete_lines();
    // curr_board.print_board(10,5);

    // cout << curr_board.game_over() << endl;
    // curr_board.get_board_value(0,8) = 1;
    // cout << curr_board.game_over() << endl;
}