#include "ttrs_pieces.h"

#define TETRIS_TYPES 7

int piece_types [7][4][4] = {
    {
        {1,0,0,0},
        {1,0,0,0},
        {1,0,0,0},
        {1,0,0,0},
    },
    {
        {1,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0},
    },
    {
        {1,0,0,0},
        {1,0,0,0},
        {1,1,0,0},
        {0,0,0,0},
    },
    {
        {0,1,0,0},
        {0,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
    },
    {
        {1,1,1,0},
        {0,1,0,0},
        {0,0,0,0},
        {0,0,0,0},
    },
    {
        {1,0,0,0},
        {1,1,0,0},
        {0,1,0,0},
        {0,0,0,0},
    },
    {
        {0,1,0,0},
        {1,1,0,0},
        {1,0,0,0},
        {0,0,0,0},
    }
};

int random_int(int min,int max){
    return rand()%(max-min + 1) + min;
}

Piece::Piece(){
    int random_piece = random_int(0,TETRIS_TYPES - 1);
    is_cube = (random_piece == 1)?true:false;
    for(int i = 0; i < PIECE_HEIGHT; ++i){
        for(int j = 0; j < PIECE_WIDTH; ++j){
            if(piece_types[random_piece][i][j] == 1){
                get_value(i,j) = 1;
            }
            else{
                get_value(i,j) = 0;
            }
        }
    }
    rotate(random_int(0,3));
}

void Piece::rotate(int n){
    if(is_cube){return;}
    for(int i = 0;i < n; ++i){
        rotate_cw();
    }
    apply_shift();
}

void Piece::rotate_cw(){
    if(is_cube){return;}
    //rotating to a temp array
    int temp[PIECE_HEIGHT][PIECE_WIDTH];
    for(int i = 0;i<PIECE_HEIGHT;++i){
        for(int j = 0 ;j<PIECE_WIDTH;++j){
            temp[i][j] = get_value(PIECE_HEIGHT-j-1,i);
        }
    }
    //copying values to original array
    for(int i = 0;i<PIECE_HEIGHT;++i){
        for(int j = 0 ;j<PIECE_WIDTH;++j){
            get_value(i,j) = temp[i][j];
        }
    }
}

int & Piece::get_value(int row, int column){
    return matrix[row][column];
}

void Piece::print_piece(){
    std::cout << "curr piece" << std::endl;
    for(int i = 0; i < PIECE_HEIGHT;++i){
        for(int j = 0;j < PIECE_WIDTH;++j){
            std::cout << get_value(i,j) << " "; 
        }
        std::cout << std::endl;
    }

}

int Piece::x_shifts(){
    //x shift
    int x_shift = 0;
    int counter;
    for(int i = 0;i< PIECE_HEIGHT ;++i){
        counter = 0;
        for(int j = 0 ;j < PIECE_WIDTH;++j){
            if(get_value(j,i)==0){
                counter++;
            }
            else{
                return x_shift;
            }
        }
        if(counter==PIECE_WIDTH){
            x_shift++;
        }
    }
    return 0;
}

int Piece::y_shifts(){      
    //x shift
    int y_shift = 0;
    int counter;
    for(int i = 0;i<PIECE_HEIGHT;++i){
        counter = 0;
        for(int j = 0 ;j<PIECE_WIDTH;++j){
            if(get_value(i,j)==0){
                counter++;
            }
            else{
                return y_shift;
            }
        }
        if(counter==PIECE_HEIGHT){
            y_shift++;
        }
    }
    return 0;
}

void Piece::apply_shift(){
    int x_shift = x_shifts();
    int y_shift = y_shifts();
    for(int i = 0; i < PIECE_HEIGHT;++i){
        for(int j = 0;j < PIECE_WIDTH;++j){
            if(get_value(i,j)==1 && !(x_shift==0 && y_shift==0)){
                get_value(i-y_shift,j-x_shift) = get_value(i,j);
                get_value(i,j)= 0;
            }
        }
    }
}