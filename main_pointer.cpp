#include "Lists_pointer.hpp"

int main()
{
    LIST_POINTER(naruto, int, int);

    naruto.insert_begin(1, 20);
    naruto.insert_begin(15, 10);
    naruto.insert_after(1, 20, 30);
    naruto.graph();

    return 0;
}
