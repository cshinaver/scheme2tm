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
	echo '(println 1738' > testfile3
	./schemeterpreter testfile3
	rm testfile3
	echo '(print)' > testfile4
	./schemeterpreter testfile4
	rm testfile4
	echo '(print (print (print "print")))' > testfile5
	./schemeterpreter testfile5
	rm testfile5
	echo '(print a (print b))' > testfile6
	./schemeterpreter testfile6
	rm testfile6
	echo '(print     "he123lo"  )' > testfile7
	./schemeterpreter testfile7
	rm testfile7
	echo '("hello")' > testfile8
	./schemeterpreter testfile8
	rm testfile8

clean:
	rm -f *.o $(TARGETS)
