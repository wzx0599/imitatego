/**
 * @file    : priority_queue.hpp
 * @author  : Wei Zixian
* @brief   : A C++ implementation of \'Priority Queue\' Max Queue
 *            本质上，一个优先堆列可以看作是一个堆，所以为了实现一个优先队列维护一个最大堆或者最小堆即可。
 *            需要注意的是，一般意义上，优先队列会有一个键值和一个实际值，键值存在的主要目的是为了表征
 *            实际值的优先级情况。即，在优先队列中需要根据键值来对数据进行排序，而在本例中键值和实际值是
 *            一样的。
 * @version : 0.1
 * @date    : 2021-02-20
 */

#include <iostream>
#include <vector>

class PriorityQueue
{
public:
    PriorityQueue() : _size(0) {}
    // PriorityQueue(const PriorityQueue &pq);
    ~PriorityQueue() {}

    void push(int elem)
    {
        _nums.push_back(elem);
        _size++;
        heapUp();
    }

    void pop()
    {
        if (isEmpty())
        {
            return;
        }

        swap(_nums[0], _nums[size() - 1]);
        _nums.pop_back();
        _size--;
        heapDown();
    }

    bool isEmpty()
    {
        return _size == 0;
    }

    size_t size()
    {
        return _size;
    }

    /**
     * @brief 考虑非空情况，成员变量_nums是需要维护的堆，对这个堆而言，其第一个数总是最大的(最大堆)或者最小的(最小堆)
     * @return int
     */
    int top()
    {
        if (isEmpty())
        {
            return int();
        }

        return _nums.front();
    }

private:
    /**
     * @brief 如果这个函数是空的话，那么这个类就是一个最基本的队列实现
     *        同时对于优先队列而言，这函数是最关键的，这里以最大堆为例。
     */
    void sort()
    {

    }

    int getLeftChildrenIndex(const int parent_index)
    {
        return parent_index * 2 + 1;
    }

    int getRightChildrenIndex(const int parent_index)
    {
        return parent_index * 2 + 2;
    }

    int getParentIndex(const int children_index)
    {
        return static_cast<int>((children_index - 1) / 2);
    }

    bool hasLeftChildren(const int parent_index)
    {
        return getLeftChildrenIndex(parent_index) < _size;
    }

    bool hasRightChildren(const int parent_index)
    {
        return getRightChildrenIndex(parent_index) < _size;
    }

    bool hasParent(const int children_index)
    {
        return getParentIndex(children_index) >= 0;
    }

    int left(const int parent_index)
    {
        return _nums[getLeftChildrenIndex(parent_index)];
    }

    int right(const int parent_index)
    {
        return _nums[getRightChildrenIndex(parent_index)];
    }

    int parent(const int children_index)
    {
        return _nums[getParentIndex(children_index)];
    }

    /**
     * @brief heapUp操作就是在一个已经排序好的堆的尾部放置需要插入的元素，然后用不断的用这个元素和父节点
     *        进行比较，直到位置合适。
     */
    void heapUp()
    {
        // 在尾部插入元素(这个步骤已经在push函数中进行了)
        // 将尾部节点不断同父节点进行比较
        int child = size() - 1;
        while (hasParent(child) && _nums[child] > parent(child)) {
            swap(_nums[child], _nums[getParentIndex(child)]);
            child = getParentIndex(child);
        }
    }

    void heapDown()
    {
        int root = 0;
        while (hasLeftChildren(root))
        {
            int child = getLeftChildrenIndex(root);
            if (hasRightChildren(root) && right(root) > left(root))
            {
                child = getRightChildrenIndex(root);
            }

            if (_nums[root] < _nums[child])
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

    std::vector<int> _nums;
    size_t _size;
};

void test()
{
    using namespace std;
    cout << "Priority Queue Test." << endl;
    auto *pq = new PriorityQueue();
    pq->push(0);
    pq->push(10);
    pq->push(5);
    pq->push(16);
    pq->push(19);
    pq->push(6);
    pq->push(4);

    while (!pq->isEmpty())
    {
        cout << pq->top() << " ";
        pq->pop();
    }
    cout << endl;
}
