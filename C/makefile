CC=g++-9
Version=-std=c++2a

all: toy_lisp math calc

toy_lisp: eval.cpp parse.cpp tokens.cpp builtin.cpp
	$(CC) $(Version) eval.cpp parse.cpp tokens.cpp builtin.cpp -o toy_lisp

math: math.cpp
	$(CC) $(Version) math.cpp -o math

calc: calc.cpp
	$(CC) $(Version) calc.cpp -o calc