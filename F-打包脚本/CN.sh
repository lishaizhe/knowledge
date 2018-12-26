CURRENT_PATH=`pwd`
PROJ_PATH="$CURRENT_PATH/Publish.android-studio/WarZ_CN"
cd $CURRENT_PATH


git checkout -- .

cd ./CCB
git checkout -- .
git checkout tilemap_release
git pull
git submodule update

cd $CURRENT_PATH
git checkout -- .
git checkout tilemap_release
git pull 

cd ./CCB/DayZResources/local
git checkout tilemap1_release
git pull
cd ../../../
git submodule update


# 设定环境变量
export NDK_ROOT=/opt/android-ndk-r9c
export ANDROID_SDK_ROOT=/opt/android-sdk-macosx
export ANDROID_HOME=/opt/android-sdk-macosx
export ANDROID_NDK_ROOT=/opt/android-ndk-r9c
export PATH=$PATH:$ANDROID_NDK_ROOT
export PATH=$PATH:$ANDROID_SDK_ROOT
export ANT_HOME=/opt/apache-ant-1.9.4
export PATH=$PATH:$ANT_HOME/bin
export PATH=$PATH:$ANDROID_SDK_ROOT/platform-tools
export PATH=$PATH:/usr/local/bin/
export PATH=$PATH:$PWD/CCB/IF/bin/
export GRADLE_HOME=gradle-2.14
export PATH=$PATH:$GRADLE_HOME/bin

curMonth=`date '+%Y%m'`
curDate=`date '+%Y%m%d'`
curTime=`date '+%H.%M.%S'`
SVN_REVISION=`git rev-list --all|wc -l`
echo "SVN_REVISION is $SVN_REVISION"
REV=$BUILD_NUMBER

#将扩展包的部分资源放在Resource目录下
sh copyExpack_ios.sh

if [ "$PACKAGE_NUM" == "1" ];then
 	echo "_____PACKAGE_NUM == 1  _____"
fi
 
echo "REV is $REV"

APK_TARGET_FOLDER="/Volumes/MAC3/LastShelter/LS_Android_V3_Release_CN/$curMonth/$curDate/Build_$BUILD_NUMBER"

if [ ! -d $APK_TARGET_FOLDER ]; then
    mkdir -p $APK_TARGET_FOLDER
fi

if [ ! -d "./android_generate" ]; then
    mkdir ./android_generate
fi

createPKM()
{
	pwd
	rm -rf $CURRENT_PATH/android_generate/*
	echo "rebuild pkm files"
    cd "$CURRENT_PATH/CCB/IF/"
    echo "call pack_android"
    sh pack_android.sh 
}


if [ "$CleanGradle" == "true" ];then
  cd $PROJ_PATH
  ./gradlew clean
  cd -
fi

current_datetime=`stat  -t " %s " upload.sh | awk '{print $10}'`
echo "current_datetime = $current_datetime"

if [ "$PACKPICTURES" == "true" ];then
    createPKM
else
    for dir in ./CCB/IFResources
	do
		(
			fileType=${dir%%/}
			#echo "________"
			cd $dir
			for pvrFile in ` find . -name "*.ccz" `
			do
				fullFileName=${pvrFile##./}
				fullFileName=${fullFileName}
				file_datetime=`stat -t " %s " $fullFileName | awk '{print $10}'`
	           	if [ $current_datetime -gt $file_datetime ];then
					echo "$dir/$fullFileName not change"
				else
					echo "$dir/$fullFileName is modified"
					createPKM
					break;
				fi
			done
		)
	done
fi
pwd
touch upload.sh	

# fix worldmap
#cp $CURRENT_PATH/CCB/DayZResources/WorldMap.tmx $CURRENT_PATH/android_generate/WorldMap.tmx
sed -i '' 's/World_1.pvr.ccz/_alpha_World_1.pkm/g' $CURRENT_PATH/CCB/DayZResources/WorldMap.tmx
sed -i '' 's/World_4.pvr.ccz/_alpha_World_4.pkm/g' $CURRENT_PATH/CCB/DayZResources/WorldMap.tmx
#cp $CURRENT_PATH/CCB/DayZResources/WorldMap1.tmx $CURRENT_PATH/android_generate/WorldMap1.tmx
sed -i '' 's/World_1.pvr.ccz/_alpha_World_1.pkm/g' $CURRENT_PATH/CCB/DayZResources/WorldMap1.tmx

# generate cpp includes
JNI_PATH="$CURRENT_PATH/proj.android-studio/jni"
cd $JNI_PATH
sh mksrc.sh

cd $PROJ_PATH
if [ "$PACKAGE_NUM" == "1" ];then
 	mv app/build.gradle app/build.gradle.1
	cp app/buildone.gradle app/build.gradle
fi

# assets config
rm -rf $PROJ_PATH/app/assets

# change vc vn
cd $PROJ_PATH/app
echo "REV=$REV"
sed -i '' "s/versionCode=\"[0-9]*\"/versionCode=\"$REV\"/g" AndroidManifest.xml

APP_VERSION_NUMBER=$(sed -n "s/.*android:versionName=\"\([0-9\.]*\)\".*/\1/p" AndroidManifest.xml)

# clean project first
cd $PROJ_PATH
if [ "$CleanGradle" == "true" ];then
./gradlew clean
fi
rm -rf $PROJ_PATH/bin
rm -rf $PROJ_PATH/app/build/outputs/apk

# create temp apk file before build
TEMP_APK_FILE_PATH="$PROJ_PATH/app/build/outputs/apk"
mkdir -p $TEMP_APK_FILE_PATH
touch $TEMP_APK_FILE_PATH/app-release.apk
touch $TEMP_APK_FILE_PATH/app-release-signed.apk

# compile apk
COCOS_CONSOLE="$CURRENT_PATH/cocos2d/cocos2d-console-3.12/bin"
COMPILE_MODE='release'
EXTRA=""
$COCOS_CONSOLE/cocos compile -s . -p android -j 8 --android-studio --ndk-toolchain arm-linux-androideabi-4.8 -m $COMPILE_MODE $EXTRA

# delété temp apk file
rm -f $TEMP_APK_FILE_PATH/app-release.apk
rm -f $TEMP_APK_FILE_PATH/app-release-signed.apk


curDate=`date '+%Y%m%d'`

if [ ! -d $APK_TARGET_FOLDER ]; then
   mkdir -p $APK_TARGET_FOLDER
fi

curTime=`date '+%H%M%S'`
 
if [ "$PACKAGE_NUM" == "1" ];then
    APK_FROM=$PROJ_PATH/app/build/outputs/apk/app-cn_0-release.apk
    APK_TARGET=$APK_TARGET_FOLDER/LS-android-$BUILD_NUMBER-Rev$APP_VERSION_NUMBER.$REV-$curTime-V3_Release-CN0.apk
    cp $APK_FROM $APK_TARGET
else
    for packagenum in $( seq 0 1 )
    do
    	echo "copy package packagenum"
         APK_FROM=$PROJ_PATH/app/build/outputs/apk/app-cn_${packagenum}-release.apk
         APK_TARGET=$APK_TARGET_FOLDER/LS-android-$BUILD_NUMBER-Rev$APP_VERSION_NUMBER.$REV-$curTime-V3_Release-CN${packagenum}.apk
         cp $APK_FROM $APK_TARGET
    done
fi

#if [ "$PACKAGE_NUM" == "1" ];then
# 	./gradlew crashlyticsUploadSymbolsCN_0Release
#else
#    for packagenum in $( seq 0 1 )
#    do
#         ./gradlew crashlyticsUploadSymbolsCN_${packagenum}Release
#    done
#fi
 

# revert changes
cd $PROJ_PATH
if [ "$PACKAGE_NUM" == "1" ];then
 	mv app/build.gradle.1 app/build.gradle
fi

#删除放到Resource目录下的扩展包
rm -rf $CURRENT_PATH/CCB/DayZResources/android_expack

echo "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"
echo $time 
echo "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"
git checkout -- .