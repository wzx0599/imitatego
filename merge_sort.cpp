/**
 * @brief : 归并排序使用的是分治的思想。
 *        : 先将数组拆分，将数组分割为最小的排序单元，然后对最小单元进行排序
 *        : 然后逐级递归回到原始数据，完成排序的任务
 *        : 下面的代码以从小到大为例
 *
 */

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
class MergeSort
{
public:
    MergeSort() {}
    ~MergeSort() {}

    void sort(std::vector<T> &nums)
    {
        int n = static_cast<T>(nums.size());
        sort(nums, 0, n - 1);
    }

private:
    // 逐级递归，直到最小单元，也就是最小的输入数组只有一个元素时
    void sort(std::vector<T> &nums, int lo, int hi)
    {
        if (lo < hi)
        {
            int mi = lo + (hi - lo) / 2;
            sort(nums, lo, mi);
            sort(nums, mi + 1, hi);
            merge(nums, lo, mi, hi);
        }
    }

    // 对数组进行逐级合并，合并的原则是对左右两个数组进行线性扫描，然后按照大小顺序放入临时数组的合适位置上
    void merge(std::vector<T> &nums, int lo, int mi, int hi)
    {
        int i = lo; // 左半数组的最左侧索引位置
        int j = mi + 1; // 右半数组的最左侧索引位置
        int k = 0;

        std::vector<T> aux(hi - lo + 1); // 临时数组用来存放临时数据

        while (i <= mi && j <= hi)
        {
            if (cmp(nums[i], nums[j]))
            {
                aux[k++] = nums[i++];
            }
            else
            {
                aux[k++] = nums[j++];
            }
        }

        // 不管是怎么样，从这里开始左半数组与右半数组中有一个是空的所以下方的代码只有一个会执行
        // 将左半数组剩余的部分拷贝到临时数组中
        while (i <= mi) {
            aux[k++] = nums[i++];
        }

        // 将右半数组剩余的部分拷贝到临时数组中
        while (j <= hi) {
            aux[k++] = nums[j++];
        }

        // 将排序好的数组拷贝到原始的数组中
        int t = lo;
        k = 0;
        while (t <= hi) {
            nums[t++] = aux[k++];
        }
    }

    Compare cmp;
};

int main(int argc, char *argv[])
{
    printf("Merge Sort Test.\r\n");
    // MergeSort<int> *ms = new MergeSort<int>();
    auto *ms = new MergeSort<int, Less<int>>();
    std::vector<int> nums = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    ms->sort(nums);

    for (const auto &num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
