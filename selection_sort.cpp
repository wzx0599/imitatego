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
class SelectionSort
{
public:
    SelectionSort() {}
    ~SelectionSort() {}

    void sort(std::vector<T> &nums)
    {
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            int target = nums[i];
            for (int j = i + 1; j < n; j++)
            {
                if (cmp(nums[j], target))
                {
                    swap(target, nums[j]);
                }
            }
            swap(target, nums[i]);
        }
    }

private:
    Compare cmp;
};

int main(int argc, char *argv[])
{
    printf("Selection Sort Test.\r\n");
    SelectionSort<int, Less<int>> *ss = new SelectionSort<int, Less<int>>();
    std::vector<int> nums = { 9, 7, 6, 8, 1, 2, 4, 3, 0, 5};
    ss->sort(nums);

    for (const auto &num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
