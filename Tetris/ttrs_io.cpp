#include "ttrs_io.h"
        
IO::IO(){
    window = SDL_CreateWindow
    (
        "Tetris", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        BOARD_WIDTH * BLOCK_SIZE,
        BOARD_HEIGHT * BLOCK_SIZE,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
}

void IO::update_board(int row,int column, int one_or_zero){
    int color = (one_or_zero ==1)?255:0;
    r.w = BLOCK_SIZE; 
    r.h = BLOCK_SIZE;
    r.x = column * BLOCK_SIZE; 
    r.y = row * BLOCK_SIZE;


    SDL_SetRenderDrawColor(renderer,color,color,color,255);
    SDL_RenderFillRect(renderer,&r);
    color = 0;
    SDL_SetRenderDrawColor(renderer,color,color,color,255);
    SDL_RenderDrawRect(renderer,&r);
    SDL_RenderPresent(renderer);
    
}

IO::~IO(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}