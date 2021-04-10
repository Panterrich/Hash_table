# Optimization Hash table

First, consider the profile of a small hash table. From previous work, we realized that _**crc hash**_ and _**MurmurHash2**_ have approximately the same distribution. Now let's take murmurhash2.

Create a table with a size of 509 by 6513 elements. The test will search for 2 words with the number of iterations 3000000. The first word is not in the table, the second is.

```c++
int main(int argc, char* argv[])
{
    FILE* dict = fopen("dict.txt", "rb");

    struct Text text = {};
    Create_text(dict, &text);

    fclose(dict);

    Hash_table<char*, char*> table(509, MurmurHash2);
    table.fill(text);

    for (size_t i = 0; i < 3000000; ++i)
    {
        table.get_value(const_cast<char*>("Jotaro"));
        table.get_value(const_cast<char*>("hash"));
    }

    Free_memory(&text);
}
```

Here are the statistics for this hash function for our table

```
Data/hash murmur.dat
Average value:      12
Variance:           13.7618
Standard deviation: 3.70969
Min:                4
Max                 25
```

To profile the program, I use callgrind, and to view the results of gprof2dot and Kcachegrind

Now compiler optimizations are disabled

![Alt text](Optimization/test0_graph.svg?raw=true "Test №0 Graph")

![Alt text](Optimization/test0_prof.png?raw=true "Test №0 Prof")

## №1 optimization

It is not difficult to notice that the main workload falls on the search function in the lists.

```c++
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
```
We can't change the list search itself, but we can shift the workload from it. To do this, make the lists shorter by increasing the size of the table.

Let's increase the table size to 3209 (was 509).

![Alt text](Optimization/test1_graph.svg?raw=true "Test №1 Graph")

![Alt text](Optimization/test1_prof.png?raw=true "Test №1 Prof")

WOW!!!! We didn't even have to rewrite anything to make the program speed up <mark>1.5 times</mark>. The workload has fallen not only on this function, but also on strcmp, since the search is already mostly carried out at the expense of the hash.

At the same time, the memory costs went only to increase the array. About 74 kilobytes (6 times larger). But that's a pittance compared to the amount of instruction decrease.

## №2 optimization 

Ok, Maybe we can still speed up the program in this way?

Try again. Let's increase the table size to 4349. On average, we now have 1.5 items in the lists. This is the most optimal value for a hash table.

![Alt text](Optimization/test2_graph.svg?raw=true "Test №2Graph")

![Alt text](Optimization/test2_prof.png?raw=true "Test №2 Prof")

The results are really amazing!!!! The program sped up by another <mark>1.64 times</mark> compared to the previous version and <mark>2.51 times</mark> compared to the base version

## №3 optimization 

So we almost removed the workload from the lists. Now the bottleneck is our hash function. It's time to change it. From previous work on MurmurHash2, the crc hash is very similar. But it should work much faster due to intrinsic instructions.

```C++
unsigned int hash_crc(char* key)
{
    unsigned int hash = 0xCAD23105U;
    
    size_t len = MY_STRLEN(key);

    for (size_t i = 0; i < len; ++i)
    {
        hash = _mm_crc32_u8(hash, (unsigned char)(key[i]));
    }

    return hash;
}
```

![Alt text](Optimization/test3_graph.svg?raw=true "Test №3 Graph")

![Alt text](Optimization/test3_prof.png?raw=true "Test №3 Prof")

Oh, no, bad luck. It even slowed down the program. But in fact, MurmurHash2 is already optimized and counts the hash by 4 characters at once, and crc hash does not do this yet.

## №4 optimization

Ok, let's try to rewrite it. 

```c++
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
```
![Alt text](Optimization/test4_graph.svg?raw=true "Test №4 Graph")

![Alt text](Optimization/test4_prof.png?raw=true "Test №4 Prof")


![Alt text](Optimization/test3_graph.svg?raw=true "Test №3 Graph")

![Alt text](Optimization/test3_prof.png?raw=true "Test №3 Prof")

Let's compare the hash functions on our data

```
Data/hash murmur.dat            Data/hash crc.dat
Average value:      1.49759     Average value:      1.49759
Variance:           1.46348     Variance:           3.39541
Standard deviation: 1.20975     Standard deviation: 1.84266
Min:                0           Min:                0
Max                 7           Max                 50
```

![Alt text](Optimization/hash.png?raw=true "Comparison hash functions")

Although crc-hash has its disadvantages in distribution, but in general they did not affect the workload of the lists, and the hash is calculated faster

# Results 

As a result, the program was speeded up <mark>3 times</mark> compared to the basic version