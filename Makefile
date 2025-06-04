#MAC 
#Caleb Walker
#10/05/2025
#Makefile

#in future make objs files go into a dir 

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic 
CPPFLAGS = -I$(INCLUDE_DIR)

SRC_DIR = src
INCLUDE_DIR = src/include

BUILD_DIR = build
LIB_DIR = lib
BIN_DIR = bin


.PHONY: all clean
all : mac
#Source and object files
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/lex.o $(BUILD_DIR)/error.o $(BUILD_DIR)/parser.o 

clean:
	rm -fr mac $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR)

all: $(TARGET)

$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)

$(LIB_DIR) :
	mkdir -p $(LIB_DIR)

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)
 
# Compile .c to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

#linking
$(BIN_DIR)/mac: $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

#symlink
mac : $(BIN_DIR)/mac
	ln -sf $(BIN_DIR)/mac mac
