#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Onegin.h"
#include "Lists_pointer.hpp"

template <typename ElemT>
struct hash_func {typedef unsigned int (*func)(ElemT);};

template <typename T>
struct remove_reference {};

template <typename T>
struct remove_reference<T&> {typedef T type;};

template <typename T>
struct remove_reference<T&&> {typedef T type;};

template <typename KeyT, typename DataT>
class Hash_table
{
    private:
        List_pointer<KeyT, DataT>* keys_;
        size_t size_;
        typename hash_func<KeyT>::func hash_;
    
    public:
        Hash_table(size_t size, typename hash_func<KeyT>::func hash = nullptr);
       ~Hash_table();

        Hash_table(const Hash_table<KeyT, DataT>& that);
        Hash_table<KeyT, DataT>& operator=(Hash_table<KeyT, DataT> that);

        Hash_table(Hash_table<KeyT, DataT>&& that);
        Hash_table<KeyT, DataT>& operator=(Hash_table<KeyT, DataT>&& that);

        void swap(Hash_table<KeyT, DataT>& that);

        unsigned int hash(KeyT key);
        void set_func(typename hash_func<KeyT>::func hash);
        DataT get_value(KeyT key);
        unsigned int set_value(KeyT key, DataT data);
        void remove(KeyT key);
        void clear();


        void unit_test(hash_func<char*>::func hash_name, const struct Text& text, const char* path, FILE* file);
        void fill(const struct Text& text);

        void translate(char* string);
        void translate(const Text& text);
};

unsigned int hash_const(char* key);
unsigned int hash_len(char* key);
unsigned int hash_sum(char* key);
unsigned int hash_code(char* key);
unsigned int hash_ror(char* key);
unsigned int hash_rol(char* key);
unsigned int hash_crc(char* key);
unsigned int hash_std(char* key);
unsigned int MurmurHash2 (char * key);

char* string_tolower(char* string);

#endif