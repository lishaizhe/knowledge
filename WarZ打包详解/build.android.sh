#!/bin/sh

#定义全局变量
export NDK_ROOT=/opt/android-ndk-r9d
export ANDROID_SDK_ROOT=/opt/android-sdk-macosx
export ANDROID_HOME=$ANDROID_SDK_ROOT
export ANDROID_NDK_ROOT=$NDK_ROOT
export PATH=$PATH:$ANDROID_NDK_ROOT
export PATH=$PATH:$ANDROID_SDK_ROOT
export ANT_HOME=/opt/apache-ant-1.9.4
export PATH=$PATH:ANT_HOME/bin
export PATH=$PATH:$ANDROID_SDK_ROOT/platform-tools
export PATH=$PATH:/usr/local/bin
export PATH=$PATH:$PWD/CCB/IF/bin/

#设置当前路径
CURRENT_PATH=`pwd`

#判断ndk路径是否存在
if [[ ! -d "$NDK_ROOT" ]]; then
	echo $NDK_ROOT error
	exit
fi

#判断sdk路径是否存在
if [[ ! -d "$ANDROID_SDK_ROOT" ]]; then
	echo $ANDROID_SDK_ROOT error
	exit
fi

#查看资源导出路径是否存在，如果不存在 mkdir
if [ ! -d "$CURRENT_PATH/android_generate" ]; then
    mkdir $CURRENT_PATH/android_generate
fi

#进行资源打包
function createPKM()
{
	rm -rf $CURRENT_PATH/android_generate/*
	rm -rf $CURRENT_PATH/Publish.android/IF_Global/assets
	pwd
	echo "rebuild pkm files"
    # 生成pkm
    cd "$CURRENT_PATH/CCB/IF/"
    echo "call pack_android"
    sh pack_android.sh   #此处衍生出资源打包
    cd "$CURRENT_PATH"
}

