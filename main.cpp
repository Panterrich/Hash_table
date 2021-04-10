#define NDEBUGMODE

#include "Hash_table.hpp"
#include "Onegin.h"
#include <locale.h>


int main(int argc, char* argv[])
{
    // FILE* dict = fopen("dict.txt", "rb");

    // struct Text text = {};
    // Create_text(dict, &text);

    // fclose(dict);

    // Hash_table<char*, char*> table(4349, hash_crc);
    // table.fill(text);

    // // FILE* file = fopen("Stat.txt", "w");
    // // table.unit_test(MurmurHash2, text, "Data/hash murmur.dat", file);
    // // table.unit_test(hash_crc, text, "Data/hash crc.dat", file);
    // // fclose(file);

    // // system("gnuplot -e \"filename=\'Data/hash crc.dat\'\"  "
    // //                "-e \"filename1=\'Data/hash murmur.dat\'\" plot.sh -persist");
    
    // for (size_t i = 0; i < 3000000; ++i)
    // {
    //     table.get_value(const_cast<char*>("Jotaro"));
    //     //table.get_value(const_cast<char*>("hash"));
    //     //table.get_value(const_cast<char*>("airport"));
    // }

    // Free_memory(&text);



    setlocale(LC_ALL, "ru_RU.cp1251");

    FILE* file   = nullptr;
    char* string = nullptr;

    struct Text text = {};

    FILE* file_dict = fopen("dict.txt", "rb");

    struct Text dict = {};
    Create_text(file_dict, &dict);

    fclose(file_dict);

    Hash_table<char*, char*> table(4339);
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

    system("opera translation.html");






    // FILE* dict = fopen("dict.txt", "rb");

    // struct Text text = {};
    // Create_text(dict, &text);

    // fclose(dict);

    // Hash_table<char*, char*> table(509);

    // FILE* file = fopen("Stat.txt", "w");

    // table.unit_test(hash_const,  text, "Data/hash const.dat",  file);
    // table.unit_test(hash_len,    text, "Data/hash len.dat",    file);
    // table.unit_test(hash_sum,    text, "Data/hash sum.dat",    file);
    // table.unit_test(hash_code,   text, "Data/hash code.dat",   file);
    // table.unit_test(hash_rol,    text, "Data/hash rol.dat",    file);
    // table.unit_test(hash_ror,    text, "Data/hash ror.dat",    file);
    // table.unit_test(hash_std,    text, "Data/hash std.dat",    file);
    // table.unit_test(hash_crc,    text, "Data/hash crc.dat",    file);
    // table.unit_test(MurmurHash2, text, "Data/hash murmur.dat", file);

    // Free_memory(&text);
    // fclose(file);

    // system("gnuplot -e \"filename=\'Data/hash const.dat\'\" " 
    //                "-e \"filename1=\'Data/hash len.dat\'\"  "  
    //                "-e \"filename2=\'Data/hash sum.dat\'\"  " 
    //                "-e \"filename3=\'Data/hash code.dat\'\" " 
    //                "-e \"filename4=\'Data/hash rol.dat\'\"  " 
    //                "-e \"filename5=\'Data/hash ror.dat\'\"  " 
    //                "-e \"filename6=\'Data/hash std.dat\'\"  " 
    //                "-e \"filename7=\'Data/hash crc.dat\'\"  "
    //                "-e \"filename8=\'Data/hash murmur.dat\'\" Script.sh -persist");

    // system("subl3 Stat.txt");

    return 0;
}