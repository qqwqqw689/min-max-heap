#include "min-max-heap.h"

int main()
{
    int p[10] = {1, 16, 2, 77, 40, 12, 45647, 4, 123, 23};
    MinMaxHeap<int> test(p,10);
    test.insert(-1);
    std::cout << test.GetMin() << std::endl;
    return 0;
}