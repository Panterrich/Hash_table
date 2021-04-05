#include "Hash_table.hpp"
#include <string.h>
#include <functional>
#include <x86intrin.h>

#define MY_STRLEN(key) (key == nullptr) ? 0 : strlen(key)

template <>
void Hash_table<char*, char*> :: fill(const struct Text& text)
{
    clear();

    for (size_t i = 0; i < text.n_lines; ++i)
    {
        char* key = strtok(text.lines[i].str, ":");
        char* translate = strtok(nullptr, "\0");
        set_value(key, translate);
    }
}

template <>
void Hash_table<char*, char*> :: unit_test(hash_func<char*>::func hash_name, const struct Text& text, const char* path, FILE* file)
{
    set_func(hash_name);
    fill(text);

    FILE* data = fopen(path, "w"); 

    double average  = text.n_lines / size_;
    double variance = 0;
    size_t min      = text.n_lines;
    size_t max      = 0;

    for (size_t i = 0; i < size_; ++i)
    {
        fprintf(data, "%lu %lu\n", i, keys_[i].get_size());
        variance += pow((keys_[i].get_size() - average), 2);

        max = (max < keys_[i].get_size()) ? keys_[i].get_size() : max;
        min = (min > keys_[i].get_size()) ? keys_[i].get_size() : min;
    }

    variance = variance / (size_ - 1);

    fprintf(file, "\n\n"
                  "%s\n"
                  "Average value:      %lg\n"
                  "Variance:           %lg\n"
                  "Standard deviation: %lg\n"
                  "Min:                %lu\n"
                  "Max                 %lu\n", path, average, variance, sqrt(variance), min, max);
   

    fclose(data);
}

unsigned int hash_const(char* key)
{
    return 1;
}

unsigned int hash_len(char* key)
{
    return MY_STRLEN(key);
} 

unsigned int hash_sum(char* key)
{
    unsigned int hash = 0;
    size_t len = MY_STRLEN(key);

    for (size_t i = 0; i < len; ++i)
    {
        hash += key[i];
    }

    return hash;
}

unsigned int hash_code(char* key)
{
    unsigned int hash = 0;
    
    if (key != nullptr) hash = key[0];

    return hash;
}

unsigned int hash_ror(char* key)
{
    unsigned int hash = 0;
    
    size_t len = MY_STRLEN(key);

    for (size_t i = 0; i < len; ++i)
    {
        hash = ((hash << 31) | (hash >> 1)) xor key[i];
    }

    return hash;
}

unsigned int hash_rol(char* key)
{
    unsigned int hash = 0;
    
    size_t len = MY_STRLEN(key);

    for (size_t i = 0; i < len; ++i)
    {
        hash = ((hash >> 31) | (hash << 1)) xor key[i];
    }

    return hash;
}

unsigned int hash_std(char* key)
{
    return std::hash<char*>{}(key);
}

unsigned int hash_crc(char* key)
{
    unsigned int hash = 0;
    
    size_t len = MY_STRLEN(key);


    for (size_t i = 0; i < len; ++i)
    {
        hash = _mm_crc32_u8(hash, (unsigned char)(key[i]));
    }

    return hash;
}

unsigned int MurmurHash2 (char * key)
{
    size_t len = MY_STRLEN(key);

    const unsigned int m = 0x5bd1e995;
    const unsigned int seed = 0;
    const int r = 24;

    unsigned int h = seed ^ len;

    const unsigned char * data = (const unsigned char *)key;
    unsigned int k;

    while (len >= 4)
    {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
        case 3:
        h ^= data[2] << 16;
        case 2:
        h ^= data[1] << 8;
        case 1:
        h ^= data[0];
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}



