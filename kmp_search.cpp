// 这段代码是参考灯神的C语言改写的C++代码 并添加了相关的注释内容

#include <iostream>
#include <vector>

using namespace std;

// 创建前缀表
// 前缀表在创建时在某种程度上是借鉴了DP算法
void mk_prefix(const string pattern, vector<int> &prefix)
{
    prefix.at(0) = 0; // 第一个位置此时应为0 否则会造成后续表的错误
    int len = 0;
    int i = 1;

    while (i < pattern.size())
    {
        // 如果当前位置也是相等的 那么前缀表内容就应该是当前len的长度
        if (pattern.at(i) == pattern.at(len))
        {
            len++;
            prefix.at(i) = len;
            i++;
        }
        else
        {
        // 因为当前位置是不一样的 那么就应该退回到前一个位置进行查找
        // 这是因为prefix存储的是能够保证相同的最长位置 所以不应该是从头开始
        // 这就相当于是在向前查找 有种stack在pop()的感觉
            // ABABCABAA
            // 0 A [default value 0]
            // 0 AB []
            // 1 ABA
            // 2 ABAB
            // 0 ABABC
            // 1 ABABCA
            // 2 ABABCAB
            // 3 ABABCABA
            // 1 ABABCABAA [退回到prefix[3]位置继续判断]
            if (len > 0)
            {
                len = prefix.at(len - 1);
            }
            else
            {
                prefix.at(i) = len; // or = 0;
                i++;
            }
        }
    }
}

// 移动前缀表
void mv_prefix(vector<int> &prefix)
{
    // 将前缀表的每个元素都向后移动一个位置
    for (int i = prefix.size() - 1; i > 0; i--)
    {
        prefix.at(i) = prefix.at(i - 1);
    }
    // 空出来的第一个位置赋值为-1 表示将数组移动到下一个位置
    prefix.at(0) = -1;
}

// KMP查找
void kmp_search(const string text, const string pattern)
{
    vector<int> prefix(pattern.size());
    mk_prefix(pattern, prefix);
    mv_prefix(prefix);

    int i = 0, j = 0;
    while (i < text.size())
    {
        // 如果到达前缀表的最后一个位置 就进行最后一步的检查 然后准备下一次查找
        if (j == pattern.size() - 1 && text.at(i) == pattern.at(j))
        {
            cout << "Found pattern at text[" << i - j << "]" << endl;
            j = prefix.at(j);
        }

        if (text.at(i) == pattern.at(j))
        {
            i++; j++;
        }
        else
        {
            j = prefix.at(j);
            // 表示在移动表前 当前位置已经是前缀表的第一个位置了 此时应该直接从下一个位置开始查找
            if (j == -1)
            {
                i++; j++;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    string text = "ABABABABCABAAB";
    string pattern = "ABABCABAA";

    kmp_search(text, pattern);

    return 0;
}
