CURRENT_PATH=`pwd`
PROJ_PATH="$CURRENT_PATH/Publish.android-studio/WarZ_Google"

cd $CURRENT_PATH
git checkout -- .
git submodule update
cd $CURRENT_PATH
git checkout -- .
git checkout tilemap
git pull 
cd ./CCB
git checkout HEAD -- .
git checkout tilemap
git pull
cd ./DayZResources/local
git checkout tilemap1
git pull
cd ../../../
#git submodule update

echo "=============================="
git branch 
git checkout tilemap
cd CCB
git branch
git checkout tilemap
cd DayZResources/local
git branch
git checkout tilemap1
cd ../../../
echo "=============================="


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
export _JAVA_OPTIONS=-Djava.net.preferIPv4Stack=true

curMonth=`date '+%Y%m'`
curDate=`date '+%Y%m%d'`
curTime=`date '+%H.%M.%S'`
#SVN_REVISION=`svn info | grep "Last Changed Rev" |  awk '{print $4}'`
SVN_REVISION=`git rev-list --all|wc -l`
echo "SVN_REVISION is $SVN_REVISION"
REV=$[ $SVN_REVISION + 4000 ]
#REV=5276
echo "REV is $REV"

#将扩展包的部分资源放在Resource目录下
sh copyExpack_ios.sh

APK_TARGET_FOLDER="/Volumes/MAC3/LastShelter/内网/$curMonth/$curDate"
#APK_TARGET_FOLDER="/Users/Shared/Jenkins/release/AgainstZ_Android_V3_Debug_Person/sudong/$curMonth/$curDate"
if [ ! -d $APK_TARGET_FOLDER ]; then
    mkdir -p $APK_TARGET_FOLDER
fi
 

if [ ! -d "./android_generate" ]; then
    mkdir ./android_generate
    rm -rf $CURRENT_PATH/tools/DiffFile/Android_*.ini
fi

createPKM()
{
	pwd
	# 运行diff脚本
	python $CURRENT_PATH/tools/DiffFile/diffFile.py
	if [ $?==0 ];then
	    cd "$CURRENT_PATH/CCB/IF/"
	    echo "call pack_android"
	    sh pack_android.sh

	    # 运行check脚本
		python $CURRENT_PATH/tools/DiffFile/repackCheckFile.py
		if [ $?==0 ];then
			echo "config update finish"
		else
			echo "config update fil"
		fi
	else
	    echo "fil"
	fi
}

current_datetime=`stat  -t " %s " upload.sh | awk '{print $10}'`
echo "current_datetime = $current_datetime"

# 打图
if [ "$Repack" == "true" ];then
	echo "rebuild pkm files"
    rm -rf $CURRENT_PATH/android_generate/*
    rm -rf $CURRENT_PATH/tools/DiffFile/Android_*.ini
    rm -rf $CURRENT_PATH/android_expack/*
    #createPKM
else
	echo ""
	#createPKM
fi
# 是否打包
if [ "$PACKPICTURES" == "true" ];then
	createPKM
fi

current_datetime=`stat  -t " %s " upload.sh | awk '{print $10}'`
echo "current_datetime = $current_datetime"

if [ "$CleanGradle" == "true" ];then
  cd $PROJ_PATH
  ./gradlew clean
  cd -
fi

cd $CURRENT_PATH
# 是否打包
#echo "PACKPICTURES = $PACKPICTURES"
#if [ "$PACKPICTURES" == "true" ];then
	#createPKM
    #for dir in ./CCB/IFResources
	#do
	#	(
	#		fileType=${dir%%/}
	#		#echo "________"
	#		cd $dir
	#		for pvrFile in ` find . -name "*.ccz" `
	#		do
	#			fullFileName=${pvrFile##./}
	#			fullFileName=${fullFileName}
	#			file_datetime=`stat -t " %s " $fullFileName | awk '{print $10}'`
	#           	if [ $current_datetime -gt $file_datetime ];then
	#				echo "$dir/$fullFileName not change"
	#			else
	#				echo "$dir/$fullFileName is modified"
	#				createPKM
	#				break;
	#			fi
	#		done
	#	)
	#done
#fi



echo "binary *.plist begin"
sh "$CURRENT_PATH/plist2bin.sh" $CURRENT_PATH/android_generate
#sh "$CURRENT_PATH/plist2bin.sh" " $CURRENT_PATH/CCB/Resources/particle
echo "binary *.plist end"

#zip -r $CURRENT_PATH/expack_$BUILD_NUMBER $CURRENT_PATH/android_expack

pwd
touch upload.sh	

# fix worldmap
#cp $CURRENT_PATH/CCB/DayZResources/WorldMap.tmx $CURRENT_PATH/android_generate/WorldMap.tmx
sed -i '' 's/World_1.pvr.ccz/_alpha_World_1.pkm/g' $CURRENT_PATH/CCB/DayZResources/WorldMap.tmx
sed -i '' 's/World_4.pvr.ccz/_alpha_World_4.pkm/g' $CURRENT_PATH/CCB/DayZResources/WorldMap.tmx
#cp $CURRENT_PATH/CCB/DayZResources/WorldMap1.tmx $CURRENT_PATH/android_generate/WorldMap1.tmx
sed -i '' 's/World_1.pvr.ccz/_alpha_World_1.pkm/g' $CURRENT_PATH/CCB/DayZResources/WorldMap1.tmx

# fix freebuild
# cp $CURRENT_PATH/CCB/Resources/ImTile.tmx $CURRENT_PATH/android_generate/ImTile.tmx
# sed -i '' 's/World_250.pvr.ccz/_alpha_World_250.pkm/g' $CURRENT_PATH/android_generate/ImTile.tmx


# generate cpp includes
JNI_PATH="$CURRENT_PATH/proj.android-studio/jni"
cd $JNI_PATH
sh mksrc.sh

#PROJ_PATH="$CURRENT_PATH/Publish.android-studio/WarZ_Google"
cd $PROJ_PATH

# assets config
rm -rf $PROJ_PATH/app/assets
cp build-cfg_debug.json build-cfg.json
cd ./app
cp build_debug.gradle build.gradle
cd ../
echo ">>>>> swap gradle"

# change vc vn
cd $PROJ_PATH/app
echo "REV=$REV"
echo "BUILD_NUMBER=$BUILD_NUMBER"   
sed -i '' "s/versionCode=\"[0-9]*\"/versionCode=\"$BUILD_NUMBER\"/g" AndroidManifest.xml

APP_VERSION_NUMBER=$(sed -n "s/.*android:versionName=\"\([0-9\.]*\)\".*/\1/p" AndroidManifest.xml)

# change package name
sed -i '' "s/apply plugin: 'com.google.gms.google-services'/\/\/apply plugin ignore: 'com.google.gms.google-services'/g" build.gradle
sed -i '' "s/com.more.dayzsurvival.gp/com.more.dayzsurvival.debug/g" build.gradle
sed -i '' "s/com.more.dayzsurvival.gp/com.more.dayzsurvival.debug/g" AndroidManifest.xml
sed -i '' "s/com.more.dayzsurvival.gp/com.more.dayzsurvival.debug/g" src/com/clash/of/notifies/HFParseCustomReceiver.java
sed -i '' "s/com.more.dayzsurvival.gp/com.more.dayzsurvival.debug/g" src/com/clash/of/notifies/FirebaseCustomMessagingService.java
sed -i '' "s/com.more.dayzsurvival.gp/com.more.dayzsurvival.debug/g" src/com/clash/of/jni/Jni.java

# 将里面的Facebook provider去掉
sed -i '' '/\<provider android:authorities="com.facebook.app.FacebookContentProvider123385965003980"/,/android:exported="true"\/\>/ d' AndroidManifest.xml


# change app name
sed "s/\"warz_app_name\">[^<]*</\"warz_app_name\">Last Shelter:Survival[Debug]</g" res/values/strings.xml > res/values/strings.tmp
mv res/values/strings.tmp  res/values/strings.xml

# clean project first
cd $PROJ_PATH
./gradlew clean
rm -rf $PROJ_PATH/bin

# compile apk
COCOS_CONSOLE="$CURRENT_PATH/cocos2d/cocos2d-console-3.12/bin"
COMPILE_MODE='debug'
#COMPILE_MODE='release'
EXTRA=""
$COCOS_CONSOLE/cocos compile -s . -p android -j 4 --android-studio --ndk-toolchain arm-linux-androideabi-4.8 -m $COMPILE_MODE $EXTRA

# push symbol to fabric
#./gradlew crashlyticsUploadSymbolsRelease

# move apk
APK_FROM=$PROJ_PATH/bin/debug/android/app-debug.apk
#APK_FROM=$PROJ_PATH/bin/release/android/WarZ-release-signed.apk
APK_TARGET=$APK_TARGET_FOLDER/LastShelter-$BUILD_NUMBER-$APP_VERSION_NUMBER-[$curTime].apk
cp $APK_FROM $APK_TARGET

#删除放到Resource目录下的扩展包
rm -rf $CURRENT_PATH/CCB/DayZResources/android_expack

# revert changes
cd $PROJ_PATH
./gradlew clean
git checkout -- .
git clean -f