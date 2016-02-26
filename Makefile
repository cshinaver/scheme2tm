SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
TARGETS = schemeterpreter
CFLAGS = -g

all: $(TARGETS)

schemeterpreter: schemeterpreter.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TARGETS)
	./test.sh

clean:
	rm -f *.o $(TARGETS)
