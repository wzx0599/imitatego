#include <iostream>

enum { ERROR, OK };
typedef int Status;
typedef int ElemType;

// 顺序栈
class SqStack
{

};

// 共享顺序栈
class SharedSqStack
{

};

// 链栈
class LinkedStack
{
public:
private:
    typedef struct StackNode
    {
        ElemType data;
        struct StackNode *next;
    } StackNode, *LinkStackPtr;
};

int main(int argc, char *argv[])
{
    return 0;
}
