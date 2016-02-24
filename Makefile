SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
TARGETS = schemeterpreter

all: $(TARGETS)

schemeterpreter: schemeterpreter.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TARGETS)
	echo '(println "Woo scheme")' > testfile
	./schemeterpreter testfile
	rm testfile

clean:
	rm -f *.o $(TARGETS)
