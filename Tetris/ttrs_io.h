#ifndef _TTRS_IO_
#define _TTRS_IO_
#include <SDL2/SDL.h>
#include "ttrs_board.h"

class IO{
    public:
        IO();
        void update_board(int row, int column, int one_or_zero);
        ~IO();
    

    private:
        SDL_Rect r;
        SDL_Window * window = NULL;
        SDL_Renderer * renderer = NULL;
};

#endif