NOISE_UTILS_DIR = ../../../libs/noiseutils/
SRC = src
CXX = g++
CFLAGS = -I/usr/include/libnoise -I$(NOISE_UTILS_DIR) -I$(SRC) -ansi -pedantic
DEBUG = -ggdb -pg -O0
LDFLAGS = -lnoise
SOURCES = $(SRC)/mapmaker.cpp $(NOISE_UTILS_DIR)/noiseutils.cpp
LIB_SOURCES = $(SRC)/libmmaker.cpp
EXECUTABLE = mapmaker 
LIB = libmmaker.o

all: lib bin

debug: CFLAGS += $(DEBUG)
debug: all 

bin: $(SOURCES)
	$(CXX) $(CFLAGS) $(SOURCES) -L. -lmmaker $(LDFLAGS) -o $(EXECUTABLE)

lib: $(LIB_SOURCES)
	$(CXX) $(CFLAGS) $(LDFLAGS) -c -fPIC $(LIB_SOURCES) -o $(LIB)
	$(CXX) -shared -o libmmaker.so  $(LIB) -lnoise
clean:
	rm -rf *o $(EXECUTABLE) 

