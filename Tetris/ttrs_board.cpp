#include "ttrs_board.h"

Piece * Board::get_curr_piece(){
    return curr_piece;
}

Board::Board(){
    for(int i = 0; i < BOARD_HEIGHT; ++i){
        for(int j = 0; j < BOARD_WIDTH; ++j){
            get_board_value(i,j) = 0;
        }
    }
    curr_piece = new Piece;
}

bool Board::auto_case(int row, int column){
    for(int i = 0; i < PIECE_HEIGHT; ++i){
        for(int j = 0; j < PIECE_WIDTH; ++j){
            if(curr_piece->get_value(i,j) == 1){
                if(i + row == BOARD_HEIGHT - 1){
                    return true;
                }
                else if(get_board_value(i + row + 1, j + column) == 1){
                    return true; 
                }
            }
        }
    }
    return false;
}

void Board::new_piece(){
    delete curr_piece; 
    curr_piece = new Piece;
}

Board::~Board(){
    delete curr_piece;
    curr_piece = nullptr; 
}

int & Board::get_board_value(int row,int column){
    return curr_board[row][column];
}

void Board::print_board(int row, int column){
    curr_piece->print_piece();
    std::cout << std::endl << "curr piece" << std::endl;
    for(int i_board = 0; i_board < BOARD_HEIGHT; ++i_board){
        for(int j_board = 0; j_board < BOARD_WIDTH; ++j_board){
            if((i_board >= row && i_board < row + PIECE_HEIGHT) && 
            (j_board >= column && j_board < column + PIECE_WIDTH) && 
            curr_piece->get_value(i_board-row,j_board-column) == 1){
                std::cout << curr_piece->get_value(i_board-row,j_board-column) << " ";
            }
            else{
                std::cout<< get_board_value(i_board,j_board) << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool Board::game_over(){
    for(int j = 0; j < BOARD_WIDTH; ++j){
        if(get_board_value(0,j)==1){
            return true;
        }
    }
    return false;
}

void Board::delete_lines(){
    int counter;
    for(int i = 0; i < BOARD_HEIGHT; ++i){
        counter = 0;
        for(int j = 0; j < BOARD_WIDTH; ++j){
            if(get_board_value(i,j)==1){counter++;}
        }
        if(counter==BOARD_WIDTH){
            shift_row_down(i);
        }
    }
}

void Board::shift_row_down(int row){
    if(row==0){
        for(int j = 0; j < BOARD_WIDTH; ++j){
            get_board_value(row,j) = 0;
        }
    }
    else{
        for(int j = 0; j < BOARD_WIDTH; ++j){
            get_board_value(row,j) = get_board_value(row-1,j);
        }
        shift_row_down(row-1);
    }

}

void Board::add_piece(int row, int column){
    for(int i_board = row, i_piece = 0; i_piece < PIECE_HEIGHT; ++i_board,++i_piece){
        for(int j_board = column, j_piece = 0; j_piece < PIECE_WIDTH; ++j_board,++j_piece){
            if(curr_piece->get_value(i_piece,j_piece) == 1){
                get_board_value(i_board,j_board) = 1;
            }
        }
    }
}

bool Board::piece_fits(int row, int column){
    for(int i_board = row, i_piece = 0; i_piece < PIECE_HEIGHT; ++i_board,++i_piece){
        for(int j_board = column, j_piece = 0; j_piece < PIECE_WIDTH; ++j_board,++j_piece){
            if(curr_piece->get_value(i_piece,j_piece) == 1){
                if(!(i_board < BOARD_HEIGHT) || !(j_board < BOARD_WIDTH && 0 <= j_board) || 
                get_board_value(i_board,j_board)==1){
                    return false;
                }
            }
        }
    }

    return true;
}
