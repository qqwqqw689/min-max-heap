#include "min-max-heap.h"

int main()
{
    int p[10] = {1, 16, 2, 77, 40, 12, 45647, 4, 123, 23};
    MinMaxHeap<int> test(p,10);

    std::cout << test.GetMax() << std::endl;
    return 0;
}