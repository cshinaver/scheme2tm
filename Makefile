SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
TARGETS = schemeterpreter
CFLAGS = -g

all: $(TARGETS)

schemeterpreter: schemeterpreter.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TARGETS)
	echo '(println "Woo scheme")' > testfile
	./schemeterpreter testfile
	rm testfile
	echo '(println 1738)' > testfile2
	./schemeterpreter testfile2
	rm testfile2

clean:
	rm -f *.o $(TARGETS)
