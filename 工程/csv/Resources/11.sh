#!/bin/sh 

## 
## convert file from GB2312 to UTF-8
## 
#

# 使用说明 ./iconv.sh + 文件名   会将源文件转换为UTF-8格式的文件
#         ./iconv.sh + 文件目录的路径 


path="$1"
unset opt
if [ "$2" = "force" ]; then
	opt="-c -s"
fi

if [ -z "$path" ]; then
	echo "nUsage: $0 <file or dir>n"
elif [ ! -e "$path" ] ; then
	echo "nERROR: destination: $path does not exist.n"
fi

if [ -f "$path" ] ; then
	echo "Converting $path (gbk --> utf-8) ... "
	if file "$path"|grep -q UTF-8 >/dev/null ; then
		echo "Already converted"
	else
		iconv -f gbk $opt -t utf-8 "$path" > /tmp/$$.tmp
		if [ $? -eq 0 ] ; then
			echo "Success"
			mv -f /tmp/$$.tmp "$path"
		else
			echo "Failed"
		fi
	fi
elif [ -d "$path" ] ; then
	find "$path" -path "$path.*" -prune -o -type f -print|while read i
	do
		dir=`dirname $i`
		file=`basename $i`
		echo "Converting $dir/$file (gbk --> utf-8) ..."
		iconv -f gbk -t utf-8 $opt "$i" > /tmp/$$.tmp 2>/dev/null
		if [ $? -eq 0 ] ; then
			echo "Success"
			mv -f /tmp/$$.tmp "$i"
		else
			echo "Failed"
		fi
	done
fi