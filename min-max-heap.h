// http://akira.ruc.dk/~keld/teaching/algoritmedesign_f03/Artikler/02/Atkinson86.pdf
#include <cmath>
#include <vector>
#include <utility>

#define LeftChild(i) i<<1
#define RightChild(i) i<<1 + 1
#define LeftLeftChild(i) i<<2
#define LeftRightChild(i) i<<2 + 1
#define RightLeftChild(i) i<<2 + 2
#define RightRightChild(i) i<<1 + 3
#define Parent(i) i>>1
#define GrandParent(i) i>>2
#define Level(i) int(std::log2(i))
#define HasLeftChild(i) LeftChild(i)<=_HeapSize
#define HasRightChild(i) RightChild(i)<=_HeapSize
#define HasLeftLeftChild(i) LeftLeftChild(i)<=_HeapSize
#define HasLeftRightChild(i) LeftRightChild(i)<=_HeapSize
#define HasRightLeftChild(i) RightLeftChild(i)<=_HeapSize
#define HasRightRightChild(i) RightRightChild(i)<=_HeapSize
#define HasChildren(i) LeftChild(i)<=_HeapSize || RightChild(i)<=_HeapSize

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
    void BuildTree();
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
    if(HasChildren(i)) // if has children
    {
        // pair : (index, value)
        auto my_comp = [](const std::pair<int,T>& z1, const std::pair<int,T>& z2)
        {
            return z1.second > z2.second;
        };

        std::priority_queue<std::pair<int,T>,
                        std::vector<std::pair<int,T>>,
                        decltype(my_comp)> pq {my_comp};
        if(HasLeftChild(i))
            pq.push({LeftChild(i),allocator(LeftChild(i))});
        if(HasRightChild(i))
            pq.push({RightChild(i),allocator(RightChild(i))});
        if(HasLeftLeftChild(i))
            pq.push({LeftLeftChild(i),allocator(LeftLeftChild(i))});
        if(HasLeftRightChild(i))
            pq.push({LeftRightChild(i),allocator(LeftRightChild(i))});
        if(HasRightLeftChild(i))
            pq.push({RightLeftChild(i),allocator(RightLeftChild(i))});
        if(HasRightChild(i))
            pq.push({RightRightChild(i),allocator(RightRightChild(i))});
        
        const auto& z = pq.top();
        int MinIndex = z.first;

        if(Parent(MinIndex)!=i) // is a grandchild
        {
            if(allocator(MinIndex) < allocator(i))
            {
                std::swap(allocator(MinIndex),allocator(i));
                if(allocator(MinIndex) > allocator(Parent(MinIndex)))
                    std::swap(allocator(MinIndex),allocator(Parent(MinIndex)));
                TrickleDownMin(MinIndex);
            }
        }
        else // is a child
        {
            if(allocator(MinIndex) < allocator(i))
                std::swap(allocator(MinIndex),allocator(i));
        }
    }
}

template<typename T>
void MinMaxHeap<T>::TrickleDownMax(int i)
{
    if(HasChildren(i)) // if has children
    {
        // pair : (index, value)
        auto my_comp = [](const std::pair<int,T>& z1, const std::pair<int,T>& z2)
        {
            return z1.second < z2.second;
        };

        std::priority_queue<std::pair<int,T>,
                        std::vector<std::pair<int,T>>,
                        decltype(my_comp)> pq {my_comp};
        if(HasLeftChild(i))
            pq.push({LeftChild(i),allocator(LeftChild(i))});
        if(HasRightChild(i))
            pq.push({RightChild(i),allocator(RightChild(i))});
        if(HasLeftLeftChild(i))
            pq.push({LeftLeftChild(i),allocator(LeftLeftChild(i))});
        if(HasLeftRightChild(i))
            pq.push({LeftRightChild(i),allocator(LeftRightChild(i))});
        if(HasRightLeftChild(i))
            pq.push({RightLeftChild(i),allocator(RightLeftChild(i))});
        if(HasRightChild(i))
            pq.push({RightRightChild(i),allocator(RightRightChild(i))});
        
        const auto& z = pq.top();
        int MaxIndex = z.first;

        if(Parent(MaxIndex)!=i) // is a grandchild
        {
            if(allocator(MaxIndex) > allocator(i))
            {
                std::swap(allocator(MaxIndex),allocator(i));
                if(allocator(MaxIndex) < allocator(Parent(MaxIndex)))
                    std::swap(allocator(MaxIndex),allocator(Parent(MaxIndex)));
                TrickleDownMax(MaxIndex);
            }
        }
        else // is a child
        {
            if(allocator(MaxIndex) > allocator(i))
                std::swap(allocator(MaxIndex),allocator(i));
        }
    }
}

template<typename T>
void MinMaxHeap<T>::BuildTree()
{
    
}