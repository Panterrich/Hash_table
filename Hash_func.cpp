#include "Hash_table.hpp"
#include <string.h>
#include <functional>
#include <x86intrin.h>

#define MY_STRLEN(key) (key == nullptr) ? 0 : strlen(key)

template <>
List_pointer_t<char*, char*>* List_pointer<char*, char*> :: find_value(char* key)
{
    assert(this != nullptr);

    List_pointer_t<char*, char*>* current_element = head();

    for (size_t index = 1; index <= size_; ++index)
    {
        if (!strcmp(current_element->key, key))
        {
            return current_element;
        }

        current_element = next(current_element);
    }

    return nullptr;
}

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

    double average  = (float) text.n_lines / size_;
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

template <>
void Hash_table<char*, char*> :: translate(char* string)
{
    FILE* page = fopen("translation.html", "w");

    fprintf(page, "<!DOCTYPE html>\n"
                  "<html>\n"
                  " <head>\n"
                  "   <meta charset=\"cp1251\">\n"
                  "  <title>font-size</title>\n"
                  "  <style>\n"
                  "  a {\n"
                  "   font-family: 'Times New Roman', Times, serif;\n"
                  "   font-size: 125%;\n" 
                  "  }\n" 
                  "   <title>:hover</title>\n"
                  "   <style>\n"
                  "    [data-tooltip] {\n"
                  "     position: relative;\n"
                  "   }\n"
                  "  [data-tooltip]::after {\n"
                  "   content: attr(data-tooltip);\n"
                  "   position: absolute;\n"
                  "   width: 300px;\n"
                  "   left: 0; top: 0;\n"
                  "   background: #3989c9;\n"
                  "   color: #fff;\n"
                  "   padding: 0.5em;\n"
                  "   box-shadow: 2px 2px 5px rgba(0, 0, 0, 0.3);\n"
                  "   pointer-events: none;\n"
                  "   opacity: 0;\n"
                  "   transition: 1s;\n"
                  "   border			: 1px solid #cccccc;\n" 
                  "  }\n"
                  "  [data-tooltip]:hover::after {\n"
                  "    opacity: 1;\n" 
                  "    op: 2em;\n"
                  "  }\n"
                  "  </style>\n"
                  "  </head>\n"
                  "  <body>\n"
                  "   <p>\n");

        char* string_lexemes = strdup(string);
        char* word           = strtok(string_lexemes, " ,.!?'\"`\n");
        char* next_word      = strtok(nullptr, " ,.!?'\"`\n");

        size_t shift       = 0;
        size_t shift_left  = 0;
        size_t shift_right = 0;

        while (word != nullptr)
        {   
            char* translate = get_value(word);

            if (translate) 
            {
                fprintf(page, " <mark title=\"%s\"> %n%s%n", translate, &shift_left, word, &shift_right);
            }

            else
            {
                fprintf(page, " %n%s%n ", &shift_left, word, &shift_right);
            }

            shift = shift_right - shift_left + word - string_lexemes;

            while (next_word != nullptr)
            {
                if (translate)
                {
                    fprintf(page, " %*s </mark>", next_word - shift - string_lexemes, string + shift);
                }

                else 
                {
                    fprintf(page, " %*s ", next_word - shift - string_lexemes, string + shift);
                }

                word      = next_word; 
                next_word = strtok(nullptr, " ,.!?'\"`\n");

                char* translate = get_value(word);

                if (translate) 
                {
                    fprintf(page, " <mark title=\"%s\"> %n%s%n", translate, &shift_left, word, &shift_right);
                }

                else
                {
                    fprintf(page, " %n%s%n ", &shift_left, word, &shift_right);
                }

                shift = shift_right - shift_left + word - string_lexemes;
            }

            if (translate)
            {
                fprintf(page, "%s </mark> ", string + shift);
            }

            else
            {
                fprintf(page, "%s ", string + shift);
            }
            
            if (next_word == nullptr) break;
        } 

    fprintf(page, " <br>\n");
    free(string_lexemes);

    fclose(page);
}


template <>
void Hash_table<char*, char*> :: translate(const Text& text)
{
    FILE* page = fopen("translation.html", "w");

    fprintf(page, "<!DOCTYPE html>\n"
                  "<html>\n"
                  " <head>\n"
                  "   <meta charset=\"cp1251\">\n"
                  "  <title>font-size</title>\n"
                  "  <style>\n"
                  "  a {\n"
                  "   font-family: 'Times New Roman', Times, serif;\n"
                  "   font-size: 125%;\n" 
                  "  }\n" 
                  "   <title>:hover</title>\n"
                  "   <style>\n"
                  "    [data-tooltip] {\n"
                  "     position: relative;\n"
                  "   }\n"
                  "  [data-tooltip]::after {\n"
                  "   content: attr(data-tooltip);\n"
                  "   position: absolute;\n"
                  "   width: 300px;\n"
                  "   left: 0; top: 0;\n"
                  "   background: #3989c9;\n"
                  "   color: #fff;\n"
                  "   padding: 0.5em;\n"
                  "   box-shadow: 2px 2px 5px rgba(0, 0, 0, 0.3);\n"
                  "   pointer-events: none;\n"
                  "   opacity: 0;\n"
                  "   transition: 1s;\n"
                  "   border			: 1px solid #cccccc;\n" 
                  "  }\n"
                  "  [data-tooltip]:hover::after {\n"
                  "    opacity: 1;\n" 
                  "    op: 2em;\n"
                  "  }\n"
                  "  </style>\n"
                  "  </head>\n"
                  "  <body>\n");

    for (size_t index = 0; index < text.n_lines; ++index)
    {   
        char* string_lexemes = strdup(text.lines[index].str);
        char* word           = strtok(string_lexemes, " -,.!?'\"`\n");
        char* next_word      = strtok(nullptr, " -,.!?'\"`\n");

        size_t shift       = 0;
        size_t shift_left  = 0;
        size_t shift_right = 0;

        while (word != nullptr)
        {   
            char* translate = get_value(word);

            if (translate != nullptr) 
            {
                fprintf(page, "<mark title=\"%s\"> %n%s%n", translate, &shift_left, word, &shift_right);
            }

            else
            {
                fprintf(page, "%n%s%n", &shift_left, word, &shift_right);
            }

            shift = shift_right - shift_left + word - string_lexemes;

            while (next_word != nullptr)
            {
                if (translate != nullptr)
                {
                    fprintf(page, "%.*s</mark>", next_word - shift - string_lexemes, text.lines[index].str + shift);
                }

                else 
                {
                    fprintf(page, "%.*s", next_word - shift - string_lexemes, text.lines[index].str + shift);
                }

                word      = next_word; 
                next_word = strtok(nullptr, " -,.!?'\"`\n");

                char* translate = get_value(word);

                if (translate != nullptr) 
                {
                    fprintf(page, " <mark title=\"%s\"> %n%s%n", translate, &shift_left, word, &shift_right);
                }

                else
                {
                    fprintf(page, "%n%s%n", &shift_left, word, &shift_right);
                }

                shift = shift_right - shift_left + word - string_lexemes;
            }

            if (translate != nullptr)
            {
                fprintf(page, "%s </mark>", text.lines[index].str + shift);
            }

            else
            {
                fprintf(page, "%s", text.lines[index].str + shift);
            }

            if (next_word == nullptr) break;
        } 

        free(string_lexemes);

        fprintf(page, "<br>\n");
    }

    fprintf(page,  " </body>\n"
                   "</html>\n");
    fclose(page);
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
    unsigned int hash = 0x5bd1e995;;
    
    size_t len = MY_STRLEN(key);
    const unsigned int* data = (const unsigned int *)key;

    while(len >= 4)
    {
        hash = _mm_crc32_u32(hash, *data);

        ++data;
        len -= 4;
    }

    switch (len)
    {
        case 1:
            hash = _mm_crc32_u8(hash, ((const unsigned char*)(data))[0]);
        case 2:           
            hash = _mm_crc32_u8(hash, ((const unsigned char*)(data))[1]);
        case 3:
            hash = _mm_crc32_u8(hash, ((const unsigned char*)(data))[2]);
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



