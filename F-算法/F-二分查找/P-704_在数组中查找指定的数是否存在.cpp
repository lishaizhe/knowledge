
#include <iostream>
using namespace std;


/*
 注意在这个题解中如下知识点。
 1.二分查找就是不停的获取中间位置来进行判定
 2.怎么获取中间值 (l&r) + ((l^r)>>1)  这个需要注意  l = 0; r = size-1
 3.在while中每做一次判定后,如果需要移动位置的话,是 mid +/-  1
 */




int search(vector<int>& nums, int target);

int main(int argc, const char * argv[]) {
 
    vector<int> temp{-1,0,3,5,9,12};
    int result = search(temp, 2);
    cout<<result<<endl;
    return 0;
}


int search(vector<int>& nums, int target)
{
    if (nums.size() == 0)
        return -1;
    int l = 0, r = nums.size()-1, mid = 0;
    while (l <= r) {
        mid = (l&r) + ((l^r)>>1);
        if (nums[mid] < target)
            l = mid+1;
        else if (nums[mid] > target)
            r = mid-1;
        else
            return mid;
    }
    return -1;
}

