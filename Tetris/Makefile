OBJS = ttrs_io.cpp ttrs_board.cpp ttrs_pieces.cpp main.cpp

OBJS_NAME = main.exe

FLAGS = -Wall -Werror

LIB = -lSDL2

all: $(OBJS)
	g++ $(OBJS) $(FLAGS) $(LIB) -o $(OBJS_NAME)
	./$(OBJS_NAME)