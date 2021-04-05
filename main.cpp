#include "Hash_table.hpp"
#include "Onegin.h"

int main()
{
    FILE* dict = fopen("dict.txt", "rb");

    struct Text text = {};
    Create_text(dict, &text);

    fclose(dict);

    Hash_table<char*, char*> table(509);

    FILE* file = fopen("Stat.txt", "w");

    table.unit_test(hash_const,  text, "Data/hash const.dat",  file);
    table.unit_test(hash_len,    text, "Data/hash len.dat",    file);
    table.unit_test(hash_sum,    text, "Data/hash sum.dat",    file);
    table.unit_test(hash_code,   text, "Data/hash code.dat",   file);
    table.unit_test(hash_rol,    text, "Data/hash rol.dat",    file);
    table.unit_test(hash_ror,    text, "Data/hash ror.dat",    file);
    table.unit_test(hash_std,    text, "Data/hash std.dat",    file);
    table.unit_test(hash_crc,    text, "Data/hash crc.dat",    file);
    table.unit_test(MurmurHash2, text, "Data/hash murmur.dat", file);

    Free_memory(&text);
    fclose(file);

    system("gnuplot -e \"filename=\'Data/hash const.dat\'\" " 
                   "-e \"filename1=\'Data/hash len.dat\'\"  "  
                   "-e \"filename2=\'Data/hash sum.dat\'\"  " 
                   "-e \"filename3='Data/hash code.dat\'\"  " 
                   "-e \"filename4=\'Data/hash rol.dat\'\"  " 
                   "-e \"filename5=\'Data/hash ror.dat\'\"  " 
                   "-e \"filename6=\'Data/hash std.dat\'\"  " 
                   "-e \"filename7=\'Data/hash crc.dat\'\"  "
                   "-e \"filename8=\'Data/hash murmur.dat\'\" Script.sh -persist");

    system("subl3 Stat.txt");

    return 0;
}