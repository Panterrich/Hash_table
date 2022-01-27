all: src/main.cpp
	g++ src/main.cpp src/Str_lib.cpp src/Hash_func.cpp -msse4.2 -march=native -g -O0 -o hashtable

pointer:
	g++ src/main_pointer.cpp -o list 
	
profile:
	valgrind --tool=callgrind ./hashtable
	gprof2dot -f callgrind callgrind.out.31466 | dot -Tsvg -o Optimization/test3_graph.svg