CC=g++
CFLAGS=-c -g -O0 -std=c++11 -Wall
LDFLAGS=
SOURCES=main.cpp cargoship.cpp cruiseship.cpp ship.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=proj4

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f core $(EXECUTABLE) $(OBJECTS)
