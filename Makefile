SOURCES = $(wildcard *.cc)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.cc=.o)
TARGETS = scheme2tm
CXXFLAGS = -g -c -std=c++11

all: $(TARGETS)

scheme2tm: schemeterpreter.o $(OBJECTS)
	$(CXX) -o $@ $^

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) $<

test: $(TARGETS)
	./test.sh

clean:
	rm -f *.o $(TARGETS)
