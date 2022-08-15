#ifndef _TTRS_BOARD_
#define _TTRS_BOARD_

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define BLOCK_SIZE 32

#include "ttrs_pieces.h"

class Board{
    public:
    Board();
    void print_board(int row, int column);
    bool piece_fits(int row, int column);
    bool auto_case(int row, int column);
    void add_piece(int row, int column);
    int & get_board_value(int row, int column);
    void delete_lines();
    bool game_over();
    void new_piece();
    Piece * get_curr_piece();
    ~Board();

    private:

    void shift_row_down(int row);
    int curr_board[BOARD_HEIGHT][BOARD_WIDTH];
    Piece * curr_piece;

};

#endif


// #ifndef _TTRS_BOARD_
// #define _TTRS_BOARD_

// #include "ttrs_pieces.h"

// //board definitions

// #define BOARD_LINE_WIDTH 6			// Width of each of the two lines that delimit the board
// #define BLOCK_SIZE 16				// Width and Height of each block of a piece
// #define BOARD_POSITION 320			// Center position of the board from the left of the screen
// #define BOARD_WIDTH 10				// Board width in blocks 
// #define BOARD_HEIGHT 20				// Board height in blocks
// #define MIN_VERTICAL_MARGIN 20		// Minimum vertical margin for the board limit 		
// #define MIN_HORIZONTAL_MARGIN 20	// Minimum horizontal margin for the board limit
// #define PIECE_BLOCKS 5			// Number of horizontal and vertical blocks of a matrix piece (after shift the max val is 4)

// enum{POS_FILLED,POS_EMPTY};

// class Board{
//     public:
//     //initialise empty board
//     Board();
//     void piece(Piece * p_in);
//     //check if piece can be placed there
//     bool possible_piece(int position_x, int position_y);
//     //add piece to the board if can be placed
//     void adding_piece(int position_x,int position_y);
//     //delete lines
//     void delete_valid_lines();
//     //game over
//     bool game_over();

//     private:
//     void Init_Board();
//     void delete_line(int height_in);

//     Piece * curr_piece; 
//     int GameBoard[BOARD_HEIGHT][BOARD_WIDTH];
// };

// #endif