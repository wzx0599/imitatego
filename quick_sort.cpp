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
class QuickSort
{
public:
    QuickSort() {}
    ~QuickSort() {}

    void sort(std::vector<T> &nums)
    {
        int n = static_cast<int>(nums.size());
        sort(nums, 0, n - 1);
    }
private:
    void sort(std::vector<T> &nums, int lo, int hi)
    {
        if (lo < hi)
        {
            // 假设基准数为子数组的第一个元素 快速
            T pivot = nums[lo];
            int i = lo;
            int j = hi;

            while (i < j)
            {
                // 先从右往左扫描，当遇到比基准数小的说明需要进行一次交换以保证基准数右侧的始终是比基准数大
                while (i < j && cmp(pivot, nums[j]))
                {
                    j--;
                }

                // 如果不是因为索引不满足条件则继续排序的过程
                // 数组不满足条件说明此时数组的一半是满足都小于或大于基准数的，否则也不会因为i >= j而跳出while循环
                // 下方注释部分不采用交换函数的原因是：
                if (i < j)
                {
                    // nums[i] = nums[j];
                    swap(nums[i], nums[j]);
                    i++;
                }

                // 然后从左向右扫描，当遇到比基准数大的数组使进行一次交换。
                while (i < j && cmp(nums[i], pivot))
                {
                    i++;
                }

                if (i < j)
                {
                    // nums[j] = nums[i];
                    swap(nums[i], nums[j]);
                    j--;
                }
            }

            // 将基准数放置在合适的位置
            nums[i] = pivot;

            // 使用分治的思想，将对左右两个数组再进行排序
            sort(nums, lo, i - 1);
            sort(nums, i + 1, hi);
        }
    }

    Compare cmp;
};

int main(int argc, char *argv[])
{
    printf("Qucik Sort Test.\r\n");
    // QuickSort<int> *qs = new QuickSort<int>();
    QuickSort<int, Less<int>> *qs = new QuickSort<int, Less<int>>();
    std::vector<int> nums = { 9, 7, 6, 8, 1, 2, 4, 3, 0, 5};
    qs->sort(nums);

    for (const auto &num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
