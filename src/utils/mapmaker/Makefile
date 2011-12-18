NOISE_UTILS_DIR = ../../../libs/noiseutils/
GDAL_DIR = /usr/include/gdal
SRC = src
CXX = g++
CFLAGS = -I/usr/include/libnoise -I$(NOISE_UTILS_DIR) -I$(GDAL_DIR) -I$(SRC) -ansi -pedantic
DEBUG = -ggdb -pg -O0
LDFLAGS = -lnoise -L/usr/lib -lgdal1.7.0
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
	echo $(GDAL_DIR)

