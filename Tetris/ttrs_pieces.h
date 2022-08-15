#ifndef _TTRS_PIECES_
#define _TTRS_PIECES_

#include <random>
#include <iostream>

#define PIECE_WIDTH 4
#define PIECE_HEIGHT 4

class Piece{
    public:
        Piece();
        void rotate(int n);
        int & get_value(int row, int column);
        void print_piece();


    private:
        void rotate_cw();

        void apply_shift();
        int x_shifts();
        int y_shifts();

        int matrix[4][4];
        bool is_cube;
};

#endif




// #ifndef _TTRS_PIECES_
// #define _TTRS_PIECES_

// #include <random>
// #include <iostream>

// //note
// // call srand((unsigned int)time(NULL)) in Main later


// //pieces class
// //there is 7 tetris kinds, my data representation will be a 4x4 matrix of ints where 0 is empty and 1 is filled 
// // piece will always start at [0,0] of the double matrix
// class Piece{
//     public:
//     Piece();
//     int GetPieceValue(int pos_x, int pos_y);
//     void RotatePiece(int n);
//     void PrintPiece();


//     private:
//     void RotatePiece();
//     void shifts();
//     void x_shifts(); void y_shifts();
//     int x_shift,y_shift;
//     int curr_piece[5][5];
//     bool is_cube; 

// };

// #endif