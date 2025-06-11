#MAC 
#Caleb Walker
#10/05/2025
#Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic 
CPPFLAGS = -I$(INCLUDE_DIR)

#fromtend files
FEND_DIR = src/frontend
#backend files
BEND_DIR = src/backend
#header files
INCLUDE_DIR = src/include

BUILD_DIR = build
LIB_DIR = lib
BIN_DIR = bin

all : mac

.PHONY: all clean

#object files that will be made
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/lex.o $(BUILD_DIR)/error.o $(BUILD_DIR)/parser.o 

clean:
	rm -fr mac $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR)

$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)

$(LIB_DIR) :
	mkdir -p $(LIB_DIR)

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)
 
# Compile frontend .c to .o
$(BUILD_DIR)/%.o: $(FEND_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: src/main.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

#linking
$(BIN_DIR)/mac: $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

#symlink
mac : $(BIN_DIR)/mac
	ln -sf $(BIN_DIR)/mac mac
