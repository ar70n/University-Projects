CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
LDLIBS= -lscreen
LDLFLAGS= -L ./lib/
IFLAGS=-I ./include
###############################################################
SRC = game.c command.c game_management.c graphic_engine.c object.c space.c player.c game_loop.c set.c enemy.c inventory.c link.c game_rules.c dialogue.c
INCLUDE = *.h
OBJ = $(SRC:.c=.o)
OBJ_DIR	= obj
OBJ_TEST = game.o command.o game_management.o graphic_engine.o object.o space.o player.o  set.o enemy.o inventory.o link.o game_rules.o dialogue.o
###############################################################

ALL_TESTS = enemy_test space_test set_test player_test inventory_test game_test command_test  object_test link_test game_management_test game_rules_test dialogue_test
EXE = anthill
all: anthill $(ALL_TESTS)


$(EXE): $(addprefix $(OBJ_DIR)/, $(OBJ)) 
	@echo ">>>>>building $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)

###############################################################################

#src: 
#	mkdir ./src ; mv -f $(SRC) ./src

#include: 
#	mkdir ./include ; mv -f $(INCLUDE) ./include
	
obj: 
	mkdir ./obj 

#lib: 
#	mkdir ./lib ; mv -f $(LDLIBS) ./lib

docs:
	doxygen ./Doxyfile

###############################################################################


# Regla para generar los archivos objeto
$(OBJ_DIR)/%.o: src/%.c  | $(OBJ_DIR)
	@echo ">>>>>building $@"
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<







#######################################################################################################

TESTS:  $(ALL_TESTS)
	@echo ">>>>>building $^"


space_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/space_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)

	


set_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/set_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)


enemy_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/enemy_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)




player_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/player_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)




object_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/object_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)




command_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/command_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)



link_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/link_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)



inventory_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/inventory_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)



game_management_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/game_management_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)



game_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/game_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)


dialogue_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/dialogue_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)
	

game_rules_test: $(addprefix $(OBJ_DIR)/, $(OBJ_TEST)) obj/game_rules_test.o
	@echo ">>>>>>Creating tests for $@"
	$(CC) $(CFLAGS) -o $@   $^ $(LDLIBS) $(LDLFLAGS) $(IFLAGS)




##############################################################################################################

DEBUG: $(OBJ)
	@echo ">>>>>building $@"
	$(CC) $(CFLAGS) -DDEBUG -o $@   ./obj/game.o ./obj/command.o ./obj/game_management.o ./obj/graphic_engine.o ./obj/object.o ./obj/space.o ./obj/player.o ./obj/game_loop.o ./obj/set.o ./obj/enemy.o ./obj/inventory.o ./obj/link.o $(LDLIBS) $(LDLFLAGS) $(IFLAGS)

	
mrun: $(EXE)
	@echo ">>>>>>Making anthill and running"
	./anthill anthill.dat

mrunval: $(EXE)
	@echo ">>>>>>Making anthill and running with valgrind"
	valgrind --leak-check=full ./anthill anthill.dat

mrundocs: docs 
	@echo "opening documentation in firefox"
	firefox ./doc/html/index.html

	

clear:
	rm -rf ./obj/*.o  

clean:
	rm -rf ./obj/*.o  $(EXE) $(ALL_TESTS) DEBUG
	
