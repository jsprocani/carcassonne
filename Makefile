SRC = ./src/
INC = ./include/
OBJ = ./obj/
BIN = ./bin/
LIB = ./lib/

CC = gcc
CFLAGS = -Wall -std=c11
LFLAGS = -lraylib -lm
EXEC = carcassonne

.PHONY: all run clean

all: $(EXEC)

run: $(EXEC)
	$(BIN)$(EXEC) tuiles_base_simplifiees

$(EXEC): engine.o parser.o init.o game.o display.o utils.o
	@mkdir -p $(BIN)
	$(CC) $(OBJ)*.o -I $(INC) -L $(LIB) -o $(BIN)$@ $(LFLAGS)
	
engine.o: $(SRC)engine.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

parser.o: $(SRC)parser.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

init.o: $(SRC)init.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

game.o: $(SRC)game.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

display.o: $(SRC)display.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

utils.o: $(SRC)utils.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

clean:
	@rm -rf $(BIN) $(OBJ)
