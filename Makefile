SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
TARGETS = schemeterpreter
CXXFLAGS = -g -c

all: $(TARGETS)

schemeterpreter: schemeterpreter.o $(OBJECTS)
	$(CXX) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) $<

test: $(TARGETS)
	./test.sh

clean:
	rm -f *.o $(TARGETS)
