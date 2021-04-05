all: main.cpp
	g++ main.cpp Str_lib.cpp  Hash_func.cpp -msse4.2 -march=native -g -o hashtable

pointer:
	g++ main_pointer.cpp -o list 
	 