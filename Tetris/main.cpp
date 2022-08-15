#include "ttrs_io.h"
#include "ttrs_board.h"
#include "ttrs_io.h"

#define DELAY 50

class Game{
    public:

    Game(){
        for(int i = 0; i < BOARD_HEIGHT; ++i){
            for(int j = 0; j < BOARD_WIDTH; ++j){
                game_io.update_board(i,j,0);
            }
            SDL_Delay(100);
        }
    }

    void print_board(){
        for(int i_board = 0; i_board < BOARD_HEIGHT; ++i_board){
            for(int j_board = 0; j_board < BOARD_WIDTH; ++j_board){
                if(game_board.get_board_value(i_board,j_board)==1){
                    game_io.update_board(i_board, j_board,1);
                }
                else{game_io.update_board(i_board, j_board,0);}
            }
        }
    }

    void print_piece(){
        Piece * curr_piece = game_board.get_curr_piece();
        for(int i_piece = 0; i_piece < PIECE_HEIGHT; ++i_piece){
            for(int j_piece = 0; j_piece < PIECE_WIDTH; ++j_piece){
                if(curr_piece->get_value(i_piece,j_piece) == 1){
                    game_io.update_board(row + i_piece, column + j_piece,1);
                }
            }
        }
    }

    void delete_piece(){
        Piece * curr_piece = game_board.get_curr_piece();
        for(int i_piece = 0; i_piece < PIECE_HEIGHT; ++i_piece){
            for(int j_piece = 0; j_piece < PIECE_WIDTH; ++j_piece){
                if(curr_piece->get_value(i_piece,j_piece) == 1){
                    game_io.update_board(row + i_piece, column + j_piece,0);
                }
            }
        }
    }

    int & get_row_pos(){
        return row;
    }

    int & get_col_pos(){
        return column;
    }

    bool game_over(){
        return game_board.game_over();
    }

    SDL_Event & get_event(){
        return event;
    }

    Board game_board;

    private:
    SDL_Event event;

    int row = -1;
    int column = 4;
    IO game_io; 
};

int main(){
    srand((unsigned int)time(NULL));
    Game game;
    bool timer;
    while(!game.game_over()){
        timer = true; 
        SDL_Delay(DELAY);
        while( SDL_PollEvent( &game.get_event() ) ){
        switch( game.get_event().type ){
            case SDL_QUIT:
                return 0; 
            case SDL_KEYDOWN:
                switch( game.get_event().key.keysym.sym ){
                    case SDLK_LEFT:
                        game.delete_piece();
                        if(game.game_board.piece_fits(game.get_row_pos(),game.get_col_pos() - 1)){
                            game.get_col_pos() = game.get_col_pos() - 1;
                        }
                        break;
                    case SDLK_RIGHT:
                        game.delete_piece();
                        if(game.game_board.piece_fits(game.get_row_pos(),game.get_col_pos() + 1)){
                            game.get_col_pos() = game.get_col_pos() + 1;
                        }
                        break;
                    case SDLK_UP:
                        game.delete_piece();
                        game.game_board.get_curr_piece()->rotate(1);
                        if(!game.game_board.piece_fits(game.get_row_pos(),game.get_col_pos() + 1)){
                            game.game_board.get_curr_piece()->rotate(3);
                        }
                        break;
                    case SDLK_DOWN:
                        timer = false;
                        break;
                    case SDLK_SPACE:
                        while(!game.game_board.auto_case(game.get_row_pos(),game.get_col_pos())){
                            game.get_row_pos() = game.get_row_pos() + 1;
                        }
                    default:
                        break;
                }
                break;   
            }
        }
        
    if(game.game_board.auto_case(game.get_row_pos(),game.get_col_pos())){
            game.game_board.add_piece(game.get_row_pos(),game.get_col_pos());
            game.game_board.delete_lines();
            game.print_board();
            game.get_row_pos() = -1;
            game.get_col_pos() = 4;
            game.game_board.new_piece();
    }
    game.delete_piece();
    game.get_row_pos() = game.get_row_pos() + 1;
    game.print_piece();
    if(timer){SDL_Delay(1000 - DELAY);}
    else{SDL_Delay(200 - DELAY);}
    }
}