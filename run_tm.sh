#!/bin/bash
# This script will create a turing machine using
# scheme2tm and execute it
# using the python library turing_machine

SCHEME_FILE=$1
EXECUTABLE=scheme2tm

usage() {
    cat <<EOF
Usage: run_tm.sh scheme_file...
EOF
    exit 1
}

if ! [ $# -eq 1 ]; then
    usage
fi

if ! [ -f $EXECUTABLE ]; then
    echo "No $EXECUTABLE executable found"
    echo
    usage
fi

if ! pip freeze 2>/dev/null | grep turing-machine &>/dev/null; then
    cat <<EOF
Please install the turing_machine python library
with $ pip install turing_machine.
EOF
    exit 1
fi


cat $SCHEME_FILE | while read prog; do
    tm=$(./$EXECUTABLE <(echo $prog))
    echo "Running Turing machine for $prog..."
    echo
    python - <<EOF
from turing_machine import TuringMachine

tm = TuringMachine($tm)

tm.debug('', step_limit=1000000000)
EOF
    echo
done

