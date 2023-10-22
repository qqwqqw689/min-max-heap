// http://akira.ruc.dk/~keld/teaching/algoritmedesign_f03/Artikler/02/Atkinson86.pdf
#include <cmath>
#include <vector>

#define LeftChild(i) i<<1
#define RightChild(i) i<<1 + 1
#define Parent(i) i>>1
#define GrandParent(i) i>>2
#define Level(i) int(std::log2(i))

// values stored at nodes on even levels are smaller than or equal to the values
// stored at their descendants

template<typename T>
class MinMaxHeap
{
private:
    std::vector<T> allocator;
    int _HeapSize;

    void TrickleDownMin(int i);
    void TrickleDownMax(int i);
public:
    void TrickleDown(int i);
};

template<typename T>
void MinMaxHeap<T>::TrickleDown(int i)
{
    if(Level(i)&1)
        TrickleDownMax(i);
    else
        TrickleDownMin(i);
}

template<typename T>
void MinMaxHeap<T>::TrickleDownMin(int i)
{

}