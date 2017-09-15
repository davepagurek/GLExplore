FILENAME=glexplore
EXECUTABLE=$(FILENAME)

CC=g++

CFLAGS= -c -Wall -Iinclude
LDFLAGS= -lglfw -framework OpenGL -framework Cocoa -framework IOKit

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -framework OpenGL
endif

SOURCES = src/main.cpp src/glad.cpp
OBJECTS = $(SOURCES:.cpp=.o)

default: build

$(EXECUTABLE): $(OBJECTS)
	$(CC) -s $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

build: $(EXECUTABLE)

clean:
	-rm $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
