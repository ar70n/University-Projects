OBJ_DIR = obj
SRC_DIR = src

CC = gcc #-ansi -pedantic
CFLAGS = -Wall
EXE = monitor miner
IFLAGS = -I ./include
#LFLAGS = 

MINER_OBJS = $(OBJ_DIR)/miner.o $(OBJ_DIR)/pow.o
MONITOR_OBJS = $(OBJ_DIR)/block.o $(OBJ_DIR)/monitor.o $(OBJ_DIR)/pow.o

all: $(EXE)

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o $(EXE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $<"
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

monitor: $(MONITOR_OBJS)
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $^

miner: $(MINER_OBJS)
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $^