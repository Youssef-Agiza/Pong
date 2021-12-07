
      
LIBS=  -lsfml-graphics -lsfml-window -lsfml-system #-lrt

SRC= ball.cpp bat.cpp main.cpp sharedMem.cpp utils.cpp globals.cpp score.cpp
HEADERS= ball.hpp bat.hpp defs.h sharedMem.h utils.h common.h globals.h score.hpp
FLAGS= -g
GCC= g++

pong: $(SRC) $(HEADERS)
	$(GCC) $(FLAGS) $(SRC) -I ./ -o pong  $(LIBS)
