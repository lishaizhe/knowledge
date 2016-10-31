#!/bin/bash
#comment 这个是shell的学习文件需要迭代

#2016/1/26
#####################################################
#首先这个地方需要注意，
#	shell -> #!/bin/sh
#	python -> #!/user/bin/python
#####################################################


#***************************************************#
#注意，这个地方
#	shell -> 变量赋值的时候，不能跟空格
#	Python -> 可以跟空格
# my_name = "li shuai zhe"
# echo $my_name

#变量名规则
#首个字母必须为字母(a-z A-Z)
#中间不能有空格，可以使用下划线
#不能使用标点符号
#不能使用bash中的关键字

# s={"rv":0,flag:1,"url":"http://www.jinhill.com","msg":"test"}  
s={"open":11.58,"high":11.99,"close":11.92,"low":11.48,"volume":86681.38,"price_change":0.31,"p_change":2.67,"ma5":11.366,"ma10":11.251,"ma20":11.543,"v_ma5":55049.74,"v_ma10":61628.07,"v_ma20":103010.58,"turnover":2.97}
parse_json(){  
  
echo $1 | sed 's/.*'$2':\([^,}]*\).*/\1/'  
  
}  
  
echo $s  
  
value=$(parse_json $s "open")  
  
echo $value


is_spine=false
if [[ is_spine == true ]]; then
	echo "is_spine true"
else
	echo "is false"
fi
# spine_prefix="ico107"
# fullFileName="_alpha_ico107000"
# for index in 0 2; do
# 	for (( i = 0; i < 10; i++ )); do
# 		spineName="_alpha_"${spine_prefix}${index}"0"${i}
# 		if [[ "$fullFileName" == $spineName ]]; then
# 			is_spine=true
# 			echo $spineName
# 			break
# 		fi
# 	done
# done
# echo $is_spine



my_name="li shuai zhe"
echo $my_name
data=1
my_name=${my_name}${data}
echo $my_name
#***************************************************#




#####################################################
#使用变量  使用 $  但是有的时候我们需要使用 {} 看下文
echo $my_name
echo "我是 ${my_name}哈哈"
#为什么有的时候要使用{}，是因为，系统解析过程中不知道my_name和 哈哈 是两个个体，所以需要拆分为两个个体
#####################################################





#***************************************************#
#只读变量  readonly
# readonly my_name
echo $my_name
# my_name="error"
echo $my_name
#***************************************************#




#####################################################
#删除变量  
#！！！！ 注意在这个时候，程序会报错，因为不可以unset readonly变量
# unset my_name
echo $my_name
#####################################################




#***************************************************#
#变量类型
#1)局部变量 局部变量在脚本或命令中定义，仅在当前shell实例中有效，其他shell启动的程序不能访问局部变量
#2)环境变量 所有的程序，包括shell启动的程序，都能访问环境变量，有些程序需要环境变量来保证其正常运行。必须要本地定义环境变量
#3)shell变量 由shell程序设置的特殊变量
#***************************************************#




#####################################################
#shell字符串
#	单引号	=》 单引号中的任何字符都会原样输出，单引号字符串中的变量是无效的
#				单引号中不能出现单引号
#	双引号 	=》 双引号中可以有变量
#				双引号里可以出现转义字符

#获取字符串长度
echo ${#my_name}
#提出子字符串
echo ${my_name:2:4}
#查找子字符串
# echo `expr index "abc" is`  #该表达式存在错误，但是注意 ` 符号
#####################################################


echo "************************完美的分界线***************************"

#！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！shell 数组！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！#

#注意，在数组中其下标从0开始
#注意，元素之间以“空格”分割
array_name=(1 2 3 4 5)

#获取单独的元素
echo ${array_name[0]}
#获取所有的元素
echo ${array_name[@]}
#获取数组元素的个数
echo ${#array_name[@]}
echo ${#array_name[*]}
#获取数组中单个元素的长度
echo ${#array_name[n]}





#！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！shell 脚本传参！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！#
#在脚本中传参，取参数的形式为 $n
#	$0为该脚本本身
#	$1第一个参数
#	$2第二个参数

#	$#	传递到脚本的参数个数
#	$*	以一个单字符串显示所有传递的参数   注意 是一个字符串
#	$$	脚本额运行的当前进程的ID号
#	$!	后台运行的最后一个进行的ID号
#	$@	与$*相同，不过他是将每一个参数都加上引号返回
#	$-	显示shell使用的当前选项，与set命令功能相同
#	$?	显示最后命令的退出状态，0表示没有错误




#！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！shell 基本运算符！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！#
#shell的运算符包括
#	算数运算符
#	关系运算符
#	布尔运算符
#	字符串运算符
#	文件测试运算符

#原生的bash不支持简单的数学运算，但是可以通过其他命令来实现， 如 awk, expr

############## 算数运算符 ################
#注意在使用expr的过程中，如当前2+2的操作，一定要注意  不可以写成2+2
value=`expr 2 + 2`
echo $value

value=`expr 20 / 3`
echo $value

num1=10
num2=2
value=`expr ${num1} \* ${num2}`  #注意*前面必须转义
echo $value


############## 关系运算符 ################
#-eq	相等
#-ne 	不相等
#-gt 	大于
#-lt	小于
#-ge	大于等于
#-le	小于等于
if [ $num1 -ne $num2 ]
	then
	echo "not equal"
fi

if [ $num1 -ne $num2 ]; then
	echo "not equal too"
fi
#经过以上两者发现 
#	1） 在[]中不可紧跟括号，需要有空格
#	2)  如果then想和if在同一行，则必须加;


############## 布尔运算符 ################
#!	非运算
#-o	或运算
#-a 与运算



############## 字符串运算符 ################
# = 判断两个字符串是否相等
# != 两个字符串是否不等
# -z 检测字符串长度是否为0
# -n 判断字符串长度是否为0
# str 检测字符串是否为空
str1="abc"
str2="ABC"
if [ $str1 = $str2 ]; then
	echo "equal"
else
	echo "not equal"
fi

if [ str ]; then
	echo "not null"
fi



############## 文件测试运算符 ################
#以下只列举普通的文件检测
#	-d	检测是否为目录
#	-f 	检测是否是普通文件
#	-r 	检测是否可读
#	-w 	检测是否可写
#	-x	检测是否可执行
#	-s 	检测是否为空【文件大小是否大于0】
#	-e 	检测文件(包括目录)是否存在

# bExist1=false
# bExist2=false
# if [ $1 ]; then
# 	bExist1=true
# fi
# if [ $2 ]; then
# 	bExist2=true
# fi
# echo $bExist1
# echo $bExist2
# echo [ $bExist1 -a $bExist2 ]
# if [ $bExist1 -a $bExist2 ]; then
# 	if [ -e $1 -a -w $2 ]; then
# 		echo "file exist and can be write"
# 	fi
# fi
##!!!!!!!!!!!!! 遗留问题
#1）怎么判定$1是否为空，$1  $2 同时为空
#2）不能打印true or false??




#！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！shell 流程控制！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！#
# for num in ${array_name[@]}
#  	do
# 	echo $num
# done
#遍历数组，需要注意的是
#1. 遍历数组的时候，我们要获取数组的所有元素，而不是直接传递一个名字，获取数组的全部元素 方法可用 ${array_name[@]}  /  ${array_name[@]}
#2. 在此时，我们不可以把do放在和for同一行，这个时候我们用 : 也是没有作用的

index=0
while [[ $index < ${#array_name[@]} ]]; do
	echo ${array_name[$index]}
	let "index++"
done
#!!! 注意,在获取数组长度的时候，一定是${#array_name[@]}/${array_name[*]}
#		数组的下标是从0开始的
#		++运算为 let "index++" ,一定注意在shell 中不存在 index=index+1,或index++ 的情况

index=0
until [ ! $index -lt 5 ] 
do
	echo "do .. until "
	let "index++"
done




############## case ################
caseValue=10
case caseValue in
	1 )	echo "caseValue = 1"
		;;
	2 )	echo "caseValue = 2"
		;;
	3 )	echo "caseValue = 3"
		;;
	4 )	echo "caseValue = 4"
		;;
	5 )	echo "caseValue = 5"
		;;
	* )	echo "caseValue = *"
		;;
esac





#！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！shell 函数 ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！#
function showLog()
{
	#同样，在函数中和shell脚本传参一个模式，都是采用$n的形式
	echo "showLog function"	
	echo "first param" $1
	echo "second param" $2
	localData=`expr $1 + $2`
	return $localData
}
showLog 1 2
echo "returnData 1 " $?
echo "returnData 2 " $?
echo "returnData 3 " $?

#!!! 关于函数 有以下几点需要注意
# 1.在定义函数的时候，我们可以用function做前缀，也可以直接定义
# 2.在函数定义中，不接受参数
# 3.函数参数通过 $n 的形式获取
# 4.函数返回值的接收，在函数调用结束后的   首个   $? 为函数调用的返回值





#！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！shell 输入输出重定向 ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！#
#command>file	将输出重定向到file
#command<file	将输入重定向到file
#command>>file	将输出以追加的方式重定向到file
#n>file			将文件描述符为n的文件重定向到file
#n>>file		将文件描述符为n的文件以追加的方式重定向到file
#n>&m 			将输出文件m和n合并
#n<&m 			将输入文件m和n合并
#<<tag			将开始标记tag和结束标记tag之间的内容作为输入

#############################################
#  /dev/null
# 如果希望之星某个命令,但又不希望在屏幕上显示输出结果，则可以直接输出到重定向/dev/null中
# /dev/null是一个特殊的文件，写入到它的内容都会被丢弃，如果尝试从该文件读取内容，则什么也读取不到



#！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！shell 文件包含 ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！#
# shell 也可以包含外部脚本， 具体做法为
#  	. filename   注意 . 和文件名中间有个空格
# 	或者是 source filename

#  test1.sh
#  test2.sh 中
#  . ./test1.sh
#  或
#  source ./test1.sh

echo "***************** 完美的分界线2 ******************"

#！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！shell 高级编程 ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！#
#清除 /var/log 下的log文件
LOG_DIR=/var/log
ROOT_UID=0  #$UID为0的时候，用户才有root权限
LINES=50	#默认的保存行数
E_XCD=66	#不能修改目录
E_NOTROOT=67	#非root用户将以error退出
echo "$UID"
if [ "$UID" -ne "$ROOT_UID" ]; then
	echo "must be root to run this script"
	exit $E_NOTROOT
fi
echo 
if [ -n "$1" ]; then  #判断当前有没有传入的参数
	lines=$1
else
	lines=LINES
fi
exit 0
cd $LOG_DIR
if [ `pwd` != "$LOG_DIR" ]; then   # 在处理log file之前,再确认一遍当前目录是否正确
	echo "can's change to $LOG_DIR"
	exit $E_XCD
fi
# 更有效的做法是
# cd /var/log || {
# 	echo "can't change to necessary directory" >&2
# 	exit $E_XCD
# }
tail -$lines messages > mesg.temp  #保存log file消息的最后部分
mv mesg.temp messages   # 变为新的log目录.
# cat /dev/null > messages
# 不在需要了，使用上面的方法更安全
cat /dev/null >wtmp 	# ': > wtmp' 和 '> wtmp'具有相同的作用
echo "Logs clean up"
exit 0

#######################################################
#上述代码解析
#首先，我们先来关注下sudo，如果是管理员，则UID应该为0，而普通用户为501，这里多句嘴
#我们可以去etc/passwd下查看，linux其实识别的为UID和GID，而并非所谓的username/password
#所以，我们才可以区别是不是root用户
# pwd 当前文件目录
































