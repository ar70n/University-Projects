OBJ_DIR = obj
SRC_DIR = src
LIBSRC_DIR = srclib
LIB_DIR = lib
LOG_DIR = log

CC = gcc #-ansi -pedantic
CFLAGS = -Wall
EXE = server
IFLAGS = -I ./includes
LFLAGS = -L ./lib -lsocket_manager -llog

SERVER_JOBS = $(OBJ_DIR)/server.o $(OBJ_DIR)/thread_manager.o $(OBJ_DIR)/http_manager.o $(OBJ_DIR)/conf_manager.o
LIBSOCKET_MANAGER_JOBS = $(OBJ_DIR)/socket_manager.o
LIBLOG_JOBS = $(OBJ_DIR)/log.o

all: liblog.a libsocket_manager.a $(EXE) 

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o $(EXE) $(LIB_DIR)/*.a
clear:
	rm -f $(OBJ_DIR)/*.o


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $<"
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ -g

$(OBJ_DIR)/%.o: $(LIBSRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $<"
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ -g

liblog.a: $(LIBLOG_JOBS)
	@mkdir -p $(LIB_DIR)
	@echo "#---------------------------"
	@echo "# Creating static library $@"
	ar rcs $(LIB_DIR)/$@ $^

libsocket_manager.a: $(LIBSOCKET_MANAGER_JOBS)
	@mkdir -p $(LIB_DIR)
	@echo "#---------------------------"
	@echo "# Creating static library $@"
	ar rcs $(LIB_DIR)/$@ $^

$(EXE): $(SERVER_JOBS)
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(SERVER_JOBS) $(LFLAGS) -g

run: all
	@mkdir -p $(LOG_DIR)
	./$(EXE)

valgrind: $(EXE)
	valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE)