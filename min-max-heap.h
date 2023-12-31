// http://akira.ruc.dk/~keld/teaching/algoritmedesign_f03/Artikler/02/Atkinson86.pdf
#include <cmath>
#include <vector>
#include <utility>
#include <limits>
#include <queue>
#include <iostream>

#define LeftChild(i) (i<<1)
#define RightChild(i) ((i<<1) + 1)
#define LeftLeftChild(i) (i<<2)
#define LeftRightChild(i) ((i<<2) + 1)
#define RightLeftChild(i) ((i<<2) + 2)
#define RightRightChild(i) ((i<<2) + 3)
#define Parent(i) (i>>1)
#define GrandParent(i) (i>>2)
#define Level(i) (int(std::log2(i)))
#define HasLeftChild(i) LeftChild(i)<=_HeapSize
#define HasRightChild(i) RightChild(i)<=_HeapSize
#define HasLeftLeftChild(i) LeftLeftChild(i)<=_HeapSize
#define HasLeftRightChild(i) LeftRightChild(i)<=_HeapSize
#define HasRightLeftChild(i) RightLeftChild(i)<=_HeapSize
#define HasRightRightChild(i) RightRightChild(i)<=_HeapSize
#define HasChildren(i) LeftChild(i)<=_HeapSize || RightChild(i)<=_HeapSize
#define HasParent(i) 1<=Parent(i)
#define HasGrandParent(i) 1<=GrandParent(i)

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
    void BubbleUp(int i);
    void BubbleUpMax(int i);
    void BubbleUpMin(int i);
    void BuildTree();
    
public:
    void TrickleDown(int i);
    T GetMax();
    T GetMin();
    void DeleteMin();
    void DeleteMax();
    void insert(T t);
    MinMaxHeap(T* p, int n); // n : number of elements in array
};

template<typename T>
void MinMaxHeap<T>::TrickleDown(int i)
{
    if(Level(i) & 1)
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
            pq.push({LeftChild(i),allocator[LeftChild(i)]});
        if(HasRightChild(i))
            pq.push({RightChild(i),allocator[RightChild(i)]});
        if(HasLeftLeftChild(i))
            pq.push({LeftLeftChild(i),allocator[LeftLeftChild(i)]});
        if(HasLeftRightChild(i))
            pq.push({LeftRightChild(i),allocator[LeftRightChild(i)]});
        if(HasRightLeftChild(i))
            pq.push({RightLeftChild(i),allocator[RightLeftChild(i)]});
        if(HasRightRightChild(i))
            pq.push({RightRightChild(i),allocator[RightRightChild(i)]});
        
        const auto& z = pq.top();
        int MinIndex = z.first;

        if(Parent(MinIndex)!=i) // is a grandchild
        {
            if(allocator[MinIndex] < allocator[i])
            {
                std::swap(allocator[MinIndex],allocator[i]);
                if(allocator[MinIndex] > allocator[Parent(MinIndex)])
                    std::swap(allocator[MinIndex],allocator[Parent(MinIndex)]);
                TrickleDownMin(MinIndex);
            }
        }
        else // is a child
        {
            if(allocator[MinIndex] < allocator[i])
                std::swap(allocator[MinIndex],allocator[i]);
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
            pq.push({LeftChild(i),allocator[LeftChild(i)]});
        if(HasRightChild(i))
            pq.push({RightChild(i),allocator[RightChild(i)]});
        if(HasLeftLeftChild(i))
            pq.push({LeftLeftChild(i),allocator[LeftLeftChild(i)]});
        if(HasLeftRightChild(i))
            pq.push({LeftRightChild(i),allocator[LeftRightChild(i)]});
        if(HasRightLeftChild(i))
            pq.push({RightLeftChild(i),allocator[RightLeftChild(i)]});
        if(HasRightRightChild(i))
            pq.push({RightRightChild(i),allocator[RightRightChild(i)]});
        
        const auto& z = pq.top();
        int MaxIndex = z.first;

        if(Parent(MaxIndex)!=i) // is a grandchild
        {
            if(allocator[MaxIndex] > allocator[i])
            {
                std::swap(allocator[MaxIndex],allocator[i]);
                if(allocator[MaxIndex] < allocator[Parent(MaxIndex)])
                    std::swap(allocator[MaxIndex],allocator[Parent(MaxIndex)]);
                TrickleDownMax(MaxIndex);
            }
        }
        else // is a child
        {
            if(allocator[MaxIndex] > allocator[i])
                std::swap(allocator[MaxIndex],allocator[i]);
        }
    }
}

template<typename T>
void MinMaxHeap<T>::BuildTree()
{
    if(_HeapSize==1 || _HeapSize==0)
        return;

    int start = Parent(_HeapSize);
    for(int i = start; i>0; i--)
        TrickleDown(i);
}

template<typename T>
MinMaxHeap<T>::MinMaxHeap(T* p, int n)
{
    _HeapSize = n;
    allocator.push_back(0);
    for(int i=0;i<_HeapSize;i++)
        allocator.push_back(p[i]);
    BuildTree();
}

template<typename T>
T MinMaxHeap<T>::GetMin()
{
    if(_HeapSize==0)
    {
        std::cout << "The heap is empty"
                  << "The maximum possible value returned" << std::endl;
        return std::numeric_limits<T>::max();
    }

    return allocator[1];
}

template<typename T>
T MinMaxHeap<T>::GetMax()
{
    if(_HeapSize==0)
    {
        std::cout << "The heap is empty"
                  << "The minimum possible value returned" << std::endl;
        return std::numeric_limits<T>::lowest();
    }

    if(_HeapSize==1)
        return allocator[1];
    
    if(_HeapSize==2)
        return allocator[2];

    return allocator[2]>allocator[3] ? allocator[2] : allocator[3];
}

template<typename T>
void MinMaxHeap<T>::DeleteMin()
{
    if(_HeapSize==0)
    {
        std::cout << "The heap is empty, operation aborted";
        return;
    }

    if(_HeapSize==1)
    {
        _HeapSize=0;
        return;
    }
    
    T temp = allocator[_HeapSize];
    _HeapSize--;
    allocator[1] = temp;
    TrickleDown(1);
}

template<typename T>
void MinMaxHeap<T>::DeleteMax()
{
    if(_HeapSize==0)
    {
        std::cout << "The heap is empty, operation aborted";
        return;
    }

    if(_HeapSize==1)
    {
        _HeapSize=0;
        return;
    }
    
    if(_HeapSize==2)
    {
        _HeapSize=1;
    }

    int MaxIndex = allocator[2]>allocator[3] ? 2 : 3;
    allocator[MaxIndex] = allocator[_HeapSize];
    _HeapSize--;
    TrickleDown(MaxIndex);
}

template<typename T>
void MinMaxHeap<T>::BubbleUpMin(int i)
{
    if(HasGrandParent(i))
    {
        if(allocator[i]<allocator[GrandParent(i)])
        {
            std::swap(allocator[i],allocator[GrandParent(i)]);
            BubbleUpMin(GrandParent(i));
        }
    }
}

template<typename T>
void MinMaxHeap<T>::BubbleUpMax(int i)
{
    if(HasGrandParent(i))
    {
        if(allocator[i]>allocator[GrandParent(i)])
        {
            std::swap(allocator[i],allocator[GrandParent(i)]);
            BubbleUpMax(GrandParent(i));
        }
    }
}

template<typename T>
void MinMaxHeap<T>::BubbleUp(int i)
{
    if(Level(i)&1) // max-level
    {
        if(HasParent(i) && allocator[i] < allocator[Parent(i)])
        {
            std::swap(allocator[i], allocator[Parent(i)]);
            BubbleUpMin(Parent(i));
        }
        else
            BubbleUpMax(i);
    }
    else // min-level
    {
        if(HasParent(i) && allocator[i] > allocator[Parent(i)])
        {
            std::swap(allocator[i], allocator[Parent(i)]);
            BubbleUpMax(Parent(i));
        }
        else
            BubbleUpMin(i);
    }
}

template<typename T>
void MinMaxHeap<T>::insert(T t)
{
    allocator.push_back(t);
    _HeapSize++;
    int i = _HeapSize;
    BubbleUp(i);
}