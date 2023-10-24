#include "min-max-heap.h"

int main()
{
    int p[9] = { 16, 2, 77, 40, 12071, 2332, 455, 123, 23};
    MinMaxHeap<int>  test(p,9);

    std::cout << test.GetMin() << std::endl;
    return 0;
}