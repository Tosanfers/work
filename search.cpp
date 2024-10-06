#include <iostream>
#include <vector>
using std::vector;

bool search(const vector<vector<int>> &arr, int tar);

int main()
{
    int tar = 3;
    vector<vector<int>> arr = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}};

    printf("%s", (search(arr, tar)) ? "true" : "false");
}

bool search(const vector<vector<int>> &arr, int tar)
{
    int len = arr.size();
    int width = arr[0].size();
    int left = 0, right = len * width - 1;
    int mid = len * width / 2;
    int midvalue = arr[mid / len][mid % len];//获取中值
    while (left <= right)//二分查找
    {
        midvalue = arr[mid / len][mid % len];
        if (midvalue < tar)
        {
            left = mid + 1;
        }
        else if (midvalue > tar)
        {
            right = mid - 1;
        }
        else if (midvalue <= tar)
            return true;
        mid = left + (right - left) / 2;
    }
    return false;
}