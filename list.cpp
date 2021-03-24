#include <iostream>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

enum { ERROR, OK };
typedef int Status;
typedef int ElemType;

// 顺序结构的线性表
class SqList
{
public:
    SqList(int capacity) : _capacity(capacity), _size(0)
    {
        _data = new ElemType[_capacity];
    }

    ~SqList()
    {
        delete[] _data;
    }

    bool lEmpty()
    {
        return _size == 0;
    }

    Status lClear()
    {
        _size = 0;
        return OK;
    }

    Status lGet(int loc, ElemType &e)
    {
        if (loc < 0 || loc >= _size)
        {
            return ERROR;
        }

        e = _data[loc];
        return OK;
    }

    Status lLocate(ElemType e, int &loc)
    {
        loc = -1;
        for (int i = 0; i < _size; i++)
        {
            if (e == _data[i])
            {
                loc = i;
            }
        }

        return loc == -1 ? ERROR : OK;
    }

    Status lInsert(int loc, ElemType e)
    {
        if (_size == _capacity || loc < 0 || loc > _size)
        {
            return ERROR;
        }

        _size++;
        for (int i = _size - 1; i > loc; i--)
        {
            _data[i] = _data[i - 1];
        }
        _data[loc] = e;
        return OK;
    }

    Status lDelete(int loc, ElemType &e)
    {
        if (lEmpty() || loc < 0 || loc >= _size)
        {
            return ERROR;
        }

        e = _data[loc];
        for (int i = loc; i < _size; i++)
        {
            _data[i] = _data[i + 1];
        }
        _size--;
        return OK;
    }

    int lLength()
    {
        return _size;
    }

private:
    ElemType* _data;
    const int _capacity;
    int _size;
};

// 单链表
class SingleLinkedList
{
public:
    SingleLinkedList() : _size(0) {}
    ~SingleLinkedList() {}

    bool lEmpty()
    {
        return _head->next == nullptr;
    }

    Status lClear()
    {
        return OK;
    }

    Status lGet(int loc, ElemType &e)
    {
        Node *p = _head->next;
        int i = 0;
        while (p && i < loc)
        {
            p = p->next;
            i++;
        }

        if (!p || i > loc)
        {
            return ERROR;
        }
        e = p->data;
        return OK;
    }

    Status lLocate(ElemType e, int &loc)
    {
        return OK;
    }

    Status lInsert(int loc, ElemType e)
    {
        return OK;
    }

    Status lDelete(int loc, ElemType e)
    {
        return OK;
    }

    int lLength()
    {
        return _size;
    }

private:
    typedef struct Node
    {
        Node (ElemType val) : data(val), next(nullptr) {}
        Node (ElemType val, Node *next) : data(val), next(next) {}
        ElemType data;
        struct Node *next;
    } Node;
    // typedef struct Node* LinkedList;

    Node* _head;
    int _size;
};

// 静态链表
class StaticLinkedList
{

};

// 循环链表
class CycleLinkedList
{

};

// 双向循环链表
class DualCycleLinkedList
{

};

int main(int argc, char *argv[])
{
    printf("Sequence List Test.\r\n");
    SqList *sq_list = new SqList(10);
    sq_list->lInsert(0, 10);
    sq_list->lInsert(1, 15);
    printf("Single Linked List Test.\r\n");
    printf("Static Linked List Test.\r\n");
    printf("Cycle Linked List Test.\r\n");
    printf("Dual-Cycle Linked List Test.\r\n");
}
