#!/bin/bash

WORKDIR="testdir"
SC=./schemeterpreter

mkdir $WORKDIR
echo '(println "Woo Scheme")' > $WORKDIR/good1
echo '(println 1739)' > $WORKDIR/good2
echo '(println (println))' > $WORKDIR/good3
echo '(println 1 2 3 4))' > $WORKDIR/good4
echo '(println 1 "meh" 3 4))' > $WORKDIR/good5
echo '(print (print (print "print" "print" 2)))' > $WORKDIR/good6
echo '(print "a" (print "b"))' > $WORKDIR/good7
echo '(println "hello" "its me")' > $WORKDIR/good8

echo '(println "Woo Scheme"' > $WORKDIR/bad1
echo '()' > $WORKDIR/bad2
echo '(println println)' > $WORKDIR/bad3
echo '(println 1 2 println))' > $WORKDIR/bad4
echo 'println 1 "meh" 3 4))' > $WORKDIR/bad5
echo '((print "hello")' > $WORKDIR/bad6
echo ')println 4)' > $WORKDIR/bad7
echo '(println 6(' > $WORKDIR/bad8
echo '(println "hello" "its me") (println "hi"' > $WORKDIR/bad9

# Test good
for f in $WORKDIR/good*; do
    echo "Testing \"$(cat $f)\""
    if ! $SC $f &>/dev/null; then
        echo "Test $f: $(cat $f) failed"
    else
        echo "Test $f passed"
    fi
done

# Test bad
for f in $WORKDIR/bad*; do
    echo "Testing \"$(cat $f)\""
    if $SC $f &>/dev/null; then
        echo "Test $f: $(cat $f) failed"
    else
        echo "Test $f passed"
    fi
done

rm -r $WORKDIR
