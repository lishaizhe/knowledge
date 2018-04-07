#!/bin/bash  
#-- 是因为bash 为其环境变量

# var1="5"  # 这个地方需要注意, shell变量赋值的时候不允许有空格
# echo $var1
# 

# strVar="i am lishuaizhe"
# strCount=${#strVar}
# echo $strCount
# 
if [ $UID -ne 0 ]; then
        echo Non root user. Please run as root.
    else
        echo Root user
fi