
      
LIBS=  -lsfml-graphics -lsfml-window -lsfml-system -lrt

SRC= ball.cpp bat.cpp main.cpp
HEADERS= ball.hpp bat.hpp defs.h
FLAGS= -g
GCC= g++

pong: $(SRC) $(HEADERS)
	$(GCC) $(FLAGS) $(SRC) -I ./ -o pong  $(LIBS)
