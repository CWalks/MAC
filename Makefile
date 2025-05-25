#MAC 
#Caleb Walker
#10/05/2025
#Makefile

#in future make objs files go into a dir 

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic 

.PHONY: all clean

#Source and object files
OBJS = main.o lex.o error.o parser.o 


#Target 
TARGET = mac 

all: $(TARGET)

#compile to object files 
lex.o: lex.c lex.h 
	$(CC) $(CFLAGS) -c lex.c

parser.o: parser.c error.h parser.h  
	$(CC) $(CFLAGS) -c parser.c

error.o: error.c lex.h error.h 
	$(CC) $(CFLAGS) -c error.c	

main.o: main.c lex.h error.h parser.h  
	$(CC) $(CFLAGS) -c main.c 



#linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -fr *.o $(TARGET) 

