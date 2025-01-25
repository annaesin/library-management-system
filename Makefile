EXE = server client #Defines compilation targets
SOBJ = server.o connect.o lib.o books.o
COBJ = client.o connect.o

CC = gcc -Wall

# Detect OS and set linking flags
ifeq ($(OS),Windows_NT)
    LFLAGS = -lws2_32
    RM = del /Q
else
    LFLAGS =
    RM = rm -f
endif

all: $(EXE)

#compiles source files and links them into an executable
server: $(SOBJ)
	$(CC) -o server $(SOBJ) $(LFLAGS)

client: $(COBJ)
	$(CC) -o client $(COBJ) $(LFLAGS)

server.o: server.c defs.h
	$(CC) -c server.c

client.o: client.c defs.h
	$(CC) -c client.c

connect.o: connect.c defs.h
	$(CC) -c connect.c

lib.o: lib.c defs.h
	$(CC) -c lib.c

books.o: books.c defs.h
	$(CC) -c books.c

#deletes compiled files 
clean:
	$(RM) $(EXE) $(SOBJ) $(COBJ)