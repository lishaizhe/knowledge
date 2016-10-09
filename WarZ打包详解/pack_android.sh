#进入当前目录
cd `dirname $0`
excludeList='bin':'Resources/'
desPrefix="$PWD/../generateResources"

#是否指定了导出目录，如果指出则按照指定目录导出
if [[ -d $1 ]]; then
	desPrefix=$1
fi

#查找为文件夹的节点
for dir in **/; do
	# =~ 匹配，表示 dir是否在excludeList中
	if [[ $excludeList =~ $dir ]]; then
		echo "This is dir do not need to pack: $dir"
		break
	fi
	#删除第一个/及其右边的字符，获得当前文件目录名字
	fileType=${dir%/}
	#进入文件目录
	cd $dir
	

done