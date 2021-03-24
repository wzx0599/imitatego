#include <iostream>
#include <cassert>

enum { ERROR, OK };
typedef int Status;
typedef char ElemType;

// 顺序存储结构的字符串
// 基于字符数组实现的字符串类
class SqString
{
public:
    SqString(int capacity) : _capacity(capacity), _size(0)
    {
        _data = new ElemType[_capacity];
    }

    SqString(const char* str) : _capacity(strlen(str))
    {
        _data = new ElemType[_capacity];
        for (int i = 0; i < _capacity; i++)
        {
            _data[i] = str[i];
        }
        _size = _capacity;
    }

    /*
    // 拷贝构造函数
    SqString(const SqString& other) : _capacity(const_cast<int>(other.sLength()))
    {
        _data = new ElemType[_capacity];
        for (int i = 0; i < _capacity; i++)
        {
            _data[i] = other.sGet(i);
        }
        _size = _capacity;
    }

    // 转移构造函数
    SqString(SqString &&other)
    {

    }*/

    ~SqString()
    {
        delete[] _data;
    }

    bool sEmpty()
    {
        return _size == 0;
    }

    Status sClear()
    {
        _size = 0;
        return OK;
    }

    ElemType sGet(int pos)
    {
        // assert(int expression) expression为false时 抛出异常
        assert(pos >= 0 && pos < _size);
        return _data[pos];
    }

    Status sPush(ElemType e)
    {
        if (_size == _capacity)
        {
            return ERROR;
        }

        _data[_size] = e;
        _size++;
        return OK;
    }

    Status sPop()
    {
        if (sEmpty())
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

    int sLength()
    {
        return _size;
    }

    char* sPrint()
    {
        return _data;
    }

private:
    ElemType* _data;
    const int _capacity;
    int _size;
};

// 链式存储结构的字符串

// 朴素的模式匹配算法
int SimpleMatch(SqString &s, SqString &t, int pos = 0)
{
    // 假设s是字典而t是待匹配字符
    assert(s.sLength() >= t.sLength());

    int i = pos;
    int j = 0;
    while (i < s.sLength() && j < t.sLength())
    {
        if (s.sGet(i) == t.sGet(j))
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1; // 匹配不成功则回退到上一次起点的下一个位置开始重新匹配
            j = 0;
        }
    }

    if (j == t.sLength())
    {
        return i - j;
    }

    return -1;
}

// KMP模式匹配算法
int KMPMatch(SqString &s, SqString &t, int pos = 0)
{
    // 假设s是字典而t是待匹配字符
    assert(s.sLength() >= t.sLength());

    return 0;
}

int main(int argc, char *argv[])
{
    printf("String Match Test.\r\n");
    SqString s("ABCCHSABCDEFHIJIJABCDD");
    SqString t("ABCDEF");
    printf("%s %s\r\n", s.sPrint(), t.sPrint());
    int simple_pos = SimpleMatch(s, t);
    int kmp_pos = KMPMatch(s, t);

    return 0;
}