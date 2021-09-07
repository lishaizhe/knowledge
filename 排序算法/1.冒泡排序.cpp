

// 冒泡排序的中心思想是从头到尾依次将小数放在前面,大数放在后面

int numArr[] = {2,4,1,5,3}
int numLength = sizeof(numArr)/sizeof(int)

for (int i = 0; i < numLength-1; ++i)
{
	for (int j = 0; j < numLength-1-i; ++j)
	{
		if (numArr[j] > numArr[j+1])
		{
			swap()
		}
	}
}

/*
为什么是这种做法
每相邻的两个依次做比较,可以将最大/小的数放置在最后的位置,所以也注意在i的时候是length-1,而j在下面的排序,因为后面的数字已经固定好了,所以就没有
必要再继续检测了,所以i的上限是 length-1-i

这块如果还不清楚的话,可以手动对上面的数据进行一次排序就可以清楚了
*/
