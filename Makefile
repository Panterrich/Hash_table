all: src/main.cpp
	g++ src/main.cpp src/Str_lib.cpp src/Hash_func.cpp -msse4.2 -march=native -g -O3 -o hashtable
