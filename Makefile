all: main.cpp
	g++ main.cpp Str_lib.cpp Hash_func.cpp -msse4.2 -march=native -g -O0 -o hashtable

pointer:
	g++ main_pointer.cpp -o list 
	
profile:
	valgrind --tool=callgrind ./hashtable
	gprof2dot -f callgrind callgrind.out.31466 | dot -Tsvg -o Optimization/test3_graph.svg