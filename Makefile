SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
TARGETS = schemeterpreter

all: $(TARGETS)

schemeterpreter: schemeterpreter.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o $(TARGETS)
