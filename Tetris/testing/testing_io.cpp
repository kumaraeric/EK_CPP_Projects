#include "ttrs_io.h"
#include <SDL2/SDL.h>


int main(){
    IO io;
    SDL_Event event;
    int x = 0, y = 0;
    while(true){
        while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            case SDL_QUIT:
                return 0; 
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        io.update_board(x,y,1);
                        ++x,++y;
                        break;
                    case SDLK_RIGHT:
                        io.update_board(x,y,0);
                        ++x,++y;
                        break;
                    case SDLK_UP:
                        break;
                    case SDLK_DOWN:
                        break;
                    default:
                        break;
                }
            }
        }

    }

}