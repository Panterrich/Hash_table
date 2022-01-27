#include "Hash_table.hpp"
#include "Onegin.h"
#include <locale.h>

int main(int argc, char* argv[])
{
    FILE* file   = nullptr;
    char* string = nullptr;

    struct Text text = {};

    FILE* file_dict = fopen("docs/dict_full.txt", "rb");

    struct Text dict = {};
    Create_text(file_dict, &dict);

    fclose(file_dict);

    Hash_table<char*, char*> table(58379);
    table.set_func(hash_crc);
    table.fill(dict);


    if (argc == 1)
    {
        printf("Enter your string for translation:\n");
        string = (char*) calloc(1000, sizeof(char*));
        fgets(string, 1000, stdin);

        table.translate(string);
        free(string);
    }

    else if (argc == 2)
    {
        file = fopen(argv[1], "rb");

        if (!file)
        {
            printf("File not found! ERROR!!!\n");
            return 1;
        }

        Create_text(file, &text);

        fclose(file);

        table.translate(text);

        Free_memory(&text);
    }

    Free_memory(&dict);

    system("opera docs/translation.html");

    return 0;
}