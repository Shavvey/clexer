# choice of compiler w/ flags
CC=gcc
FLAGS=-W -Wall -g
# sdl flags and included libs
# executable name, object files to be created, and dependencies for object files
EXEC=clexer
OBJS=src/lexer.c src/main.c
DEPS=src/lexer.h

# make dependencies to create the final executable
all: $(EXEC)

# simplified rule that makes all object files from their header and source
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c  -o $@ $<

# rule to make the final executable from the created object files
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(OBJS) -o $(EXEC) 

# clean out the object files and the final executable
clean:
	rm $(EXEC) src/*.o
