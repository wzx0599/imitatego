#include <iostream>
#include <vector>

template<class T>
struct Greater
{
    bool operator()(const T& a, const T& b) const
    {
        return a > b;
    }
};

template<class T>
struct Less
{
    bool operator()(const T& a, const T& b) const
    {
        return a < b;
    }
};

template<class T, class Compare=Greater<T>>
class MaxHeap
{
public:
    MaxHeap() : _size(0) {}

    void push(T n)
    {
        _nums.push_back(n);
        _size++;
        heapUp();
    }

    void pop()
    {
        swap(_nums[0], _nums[size() - 1]);
        _nums.pop_back();
        _size--;
        heapDown();
    }

    T top()
    {
        return _nums[0];
    }

    int size()
    {
        return _size;
    }

private:
    int parentIndex(int index)
    {
        return (index - 1) / 2;
    }

    int leftIndex(int index)
    {
        return index * 2 + 1;
    }

    int rightIndex(int index)
    {
        return index * 2 + 2;
    }

    T parent(int index)
    {
        return _nums[parentIndex(index)];
    }

    T left(int index)
    {
        return _nums[leftIndex(index)];
    }

    T right(int index)
    {
        return  _nums[rightIndex(index)];
    }

    bool hasParent(int index)
    {
        return parentIndex(index) >= 0;
    }

    bool hasLeft(int index)
    {
        return leftIndex(index) < _size;
    }

    bool hasRight(int index)
    {
        return rightIndex(index) < _size;
    }

    void heapUp()
    {
        int index = _size - 1;
        while (hasParent(index) && cmp(_nums[index], _nums[parentIndex(index)]))
        {
            swap(_nums[index], _nums[parentIndex(index)]);
            index = parentIndex(index);
        }
    }

    void heapDown()
    {
        int root = 0;
        while (hasLeft(root))
        {
            int child = leftIndex(root);
            if (hasRight(root) && cmp(right(root), left(root)))
            {
                child = rightIndex(root);
            }

            if (cmp(_nums[child], _nums[root]))
            {
                swap(_nums[root], _nums[child]);
                root = child;
            }
            else
            {
                break;
            }
        }
    }

    std::vector<T> _nums;
    Compare cmp;
    int _size;
};

int main(int argc, char *argv[])
{
    printf("Maximum Heap Test.\r\n");
    MaxHeap<int> *mh = new MaxHeap<int>();
    // MaxHeap<int, Less<int>> *mh = new MaxHeap<int, Less<int>>();
    mh->push(10);
    mh->push(11);
    mh->push(13);
    mh->push(12);
    mh->push(16);
    mh->push(18);
    mh->push(15);
    mh->push(17);
    mh->push(14);
    mh->push(19);
    mh->push(15);
    mh->push(17);

    int n = mh->size();
    for (int i = 0; i < n; i++)
    {
        std::cout << mh->top() << " ";
        mh->pop();
    }
    std::cout << std::endl;
}
