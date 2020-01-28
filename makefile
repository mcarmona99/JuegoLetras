INC = include
OBJ = obj
SRC = src
BIN = bin
CXX = g++
CPPFLAGS = #-Wall -g


all: $(BIN)/Juego

# ************ Compilación de módulos ************

$(BIN)/Juego : $(OBJ)/juego.o
	$(CXX) -o $(BIN)/Juego $(OBJ)/juego.o

$(OBJ)/juego.o : $(INC)/Diccionario.h $(INC)/letras.h $(SRC)/juegoLetras.cpp
	$(CXX) $(CPPFLAGS) -I./$(INC) -c -o $(OBJ)/juego.o $(SRC)/juegoLetras.cpp

# ************ Limpieza ************
clean :
	echo "Limpiando..."
	rm -f $(OBJ)/*.o

mrproper : clean
	rm -f $(BIN)/* doc/html/*
