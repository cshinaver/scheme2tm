SOURCES = $(wildcard *.cc)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.cc=.o)
TARGETS = schemeterpreter
CXXFLAGS = -g -c -std=c++11

all: $(TARGETS)

schemeterpreter: schemeterpreter.o $(OBJECTS)
	$(CXX) -o $@ $^

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) $<

test: $(TARGETS)
	./test.sh

clean:
	rm -f *.o $(TARGETS)
