FILE *fp = fopen(fileutils->getSuitableFOpen(fullPath).c_str(), mode);
CC_BREAK_IF(!fp);
fseek(fp,0,SEEK_END);
size = ftell(fp);
fseek(fp,0,SEEK_SET);

size 即为文件的大小

SEEK_SET  //设置指针到文件头
SEEK_CUR  //将读取指针指向当前位置
SEEK_END  //设置当前为文件结尾

//中心思想  
//1.设置指针到文件结尾处 。然后通过指针的偏移,计算出文件的大小 ，然后再将指针设置回来



/*
对应文件的指针偏移，在函数定义中并没有真正的说明清楚返回值，对于offset当为正数的时候是向文件尾偏移的，当为负数的时候是向文件头方向偏移的，
这里主要是要注意偏移的大小和文件大小边界的关系。
 
当offset是向文件尾方向偏移的时候，无论偏移量是否超出文件尾，fseek都是返回0，当偏移量没有超出文件尾的时候，
文件指针式指向正常的偏移地址的，当偏移量超出文件尾的时候，文件指针是指向文件尾的。并不会返回偏移出错-1值。

当offset是向文件头方向偏移的时候，如果offset没有超出文件头，是正常偏移，文件指针指向正确的偏移地址，fseek返回值为0.
当offset超出文件头时，fseek返回出错-1值，文件指针不变还是处于原来的地址。
*/