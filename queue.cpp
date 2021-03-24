
#include <iostream>

enum { ERROR, OK };
typedef int Status;
typedef int ElemType;

// 顺序队列
class SqQueue
{
public:
    SqQueue(int capacity) : _capacity(capacity), _size(0)
    {
        _data = new ElemType[_capacity];
    }

    ~SqQueue()
    {
        delete[] _data;
    }

    bool qEmpty()
    {
        return _size == 0;
    }

    Status qClear()
    {
        _size = 0;
        return OK;
    }

    Status qHead(ElemType &e)
    {
        if (qEmpty())
        {
            return ERROR;
        }

        e = _data[0];
        return OK;
    }

    Status qPush(ElemType e)
    {
        if (_size == _capacity)
        {
            return ERROR;
        }

        _data[_size] = e;
        _size++;
        return OK;
    }

    Status qPop()
    {
        if (qEmpty())
        {
            return ERROR;
        }

        for (int i = 1; i < _size; i++)
        {
            _data[i - 1] = _data[i];
        }
        _size--;
        return OK;
    }

    int qLength()
    {
        return _size;
    }

private:
    ElemType* _data;
    const int _capacity;
    int _size;
};

// 循环队列
class CycleQueue
{
public:
    CycleQueue(int capacity) : _capacity(capacity), _head(0), _tail(0)
    {
        _data = new ElemType[_capacity];
    }

    ~CycleQueue()
    {
        delete[] _data;
    }

    bool qEmpty()
    {
        return false;
    }

    Status qClear()
    {
        _head = 0;
        _tail = 0;
        return OK;
    }

    Status qHead(ElemType &e)
    {
        if (qEmpty())
        {
            return ERROR;
        }

        e = _data[0];
        return OK;
    }

    Status qPush(ElemType e)
    {
        return OK;
    }

    Status qPop()
    {
        if (qEmpty())
        {
            return ERROR;
        }

        return OK;
    }

    int qLength()
    {
        return 0;
    }

private:
    ElemType* _data;
    const int _capacity;
    int _head;
    int _tail;
};

// 链队列
class LinkedQueue
{
public:
private:
};

int main(int argc, char *argv[])
{
    using namespace std;
    printf("Sequence Queue Test.\r\n");
    SqQueue *sq_queue = new SqQueue(10);
    cout << sq_queue->qLength() << " ";
    sq_queue->qPush(11);
    ElemType e;
    sq_queue->qHead(e);
    cout << e << " " << endl;
}
