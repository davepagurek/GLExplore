FILENAME=glexplore
EXECUTABLE=$(FILENAME)

CC=g++

CFLAGS= -std=c++11 -c -Wall -Iinclude
LDFLAGS= `pkg-config --static --libs glfw3`

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -framework OpenGL
endif

SOURCES = $(wildcard src/*.cpp)
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
