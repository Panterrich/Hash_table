all: main.cpp
	g++ main.cpp Str_lib.cpp Hash_func.cpp -msse4.2 -march=native -g -O3 -o hashtable
