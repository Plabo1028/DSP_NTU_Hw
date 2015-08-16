SRIPATH=/tmp2/b97080/srilm-1.5.10

MACHINE_TYPE=i686-m64

CXX=g++
CXXFLAGS=-O3 -I$(SRIPATH)/include

vpath lib%.a $(SRIPATH)/lib/$(MACHINE_TYPE)

TARGET=disambig
SRC = disambig.cpp tool.cpp
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ) -loolm -ldstruct -lmisc
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) $(OBJ) $(TARGET)
	$(RM) -f *~
