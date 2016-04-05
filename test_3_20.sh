#首先在这个地方有个疑问，其实我们使用的shell脚本是需要有他的环境的，为什么在warZ中，却没有

#进入当前的全部路径
cd `dirname $0`


#这个地方存在的知识点，  
	#  : 表示什么意思
excludeList='bin/':'Resource/'
#这个地方存在一个知识点，如果是单引号，我们是没有字符串替换功能的，所以在这个时候，pwd是必须为双引号包含的
desPrefix="$PWD/../generateResource"

#如果参数1为一个目录，则我们将目的地址修改为此，否则，我们还是按照上面的generateResource
if [[ -d $1 ]]; then
	desPrefix=$1
fi

#这个是遍历在该文件夹目录下存在二级目录的文件夹
for dir in **/; do
	if [[ $excludeList =~ $dir ]]; then
		echo "this dir do not need pack : $dir"
		break
	fi
	
	


done


