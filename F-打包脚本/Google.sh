CURRENT_PATH=`pwd`
PROJ_PATH="$CURRENT_PATH/Publish.android-studio/WarZ_Google"
cd $CURRENT_PATH

git checkout -- .
git submodule update
cd $CURRENT_PATH
git checkout -- .
git checkout tilemap_release
git pull 

cd ./CCB
git checkout -- .
git checkout tilemap_release
git pull


cd ./DayZResources/local
git checkout tilemap1_release
git pull

# 删除无用的语言文件！！

rm -rf text_wow_*
rm -rf text_roe_*
rm -rf text_q_zh_CN*
rm -rf roe_plot*
rm -rf roe_guide*
rm -rf roe_exchange.xml
rm -rf q_text_zh_CN*
rm -rf q_text_en*
rm -rf q_plot*
rm -rf q_guide*
cd ../../../


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
SVN_REVISION=`git rev-list --all|wc -l`
echo "SVN_REVISION is $SVN_REVISION"
#REV=$[ $SVN_REVISION + 8745 ]
REV=$BUILD_NUMBER
#REV="24"$REV
#如果需要打一个带支付的包 把下边这句打开
#REV="79"
echo "REV is $REV"

APK_TARGET_FOLDER="/Volumes/MAC3/LastShelter/release/$curMonth/$curDate"
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

rm -rf $CURRENT_PATH/android_expack/Expack 
cp -rf $CURRENT_PATH/android_generate/Expack  $CURRENT_PATH/android_expack
cp -rf $CURRENT_PATH/android_expack $CURRENT_PATH/android_generate
rm -rf $CURRENT_PATH/android_generate/android_expack/Expack

echo "binary *.plist begin"
sh "$CURRENT_PATH/plist2bin.sh" $CURRENT_PATH/android_generate
echo "binary *.plist end"


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

# assets config
rm -rf $PROJ_PATH/app/assets
cp build-cfg_default.json build-cfg.json

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
EXTRA="--daemon --parallel --offline"
$COCOS_CONSOLE/cocos compile -s . -p android -j 8 --android-studio --ndk-toolchain arm-linux-androideabi-4.8 -m $COMPILE_MODE $EXTRA

# delété temp apk file
rm -f $TEMP_APK_FILE_PATH/app-release.apk
rm -f $TEMP_APK_FILE_PATH/app-release-signed.apk


################################################################################
cd $CURRENT_PATH
#put versionCode in OBB file
echo $BUILD_NUMBER > ./android_expack/expackver.ini
zip -r  expack_$BUILD_NUMBER.obb ./android_expack
cp $CURRENT_PATH/expack_$BUILD_NUMBER.obb "/Volumes/MAC3/LastShelter/google_obb/"
# set OBB number
md5=`md5sum $CURRENT_PATH/expack_$BUILD_NUMBER.obb|awk '{print $1}'`
sed -i "" "s/OBBMD5=.*/OBBMD5=$md5/g" $PROJ_PATH/app/assets/DayZResources/config.ini
sed -i "" "s/OBBNUMBER=.*/OBBNUMBER=$BUILD_NUMBER/g" $PROJ_PATH/app/assets/DayZResources/config.ini

#上传到服务器
chmod 644 $CURRENT_PATH/expack_$BUILD_NUMBER.obb
scp $CURRENT_PATH/expack_$BUILD_NUMBER.obb root@169.44.69.204:/data/htdocs/lastshelter/obb
cd -
################################################################################


for packagenum in $( seq 0 1 )
do
	if [ "$packagenum" == "1" ]; then
    	rm -rf $PROJ_PATH/app/assets/DayZTexture/Expack
        rm -rf $PROJ_PATH/app/assets/DayZTexture/android_expack
        sed -i "" "s/FULLAPK=.*/FULLAPK=0/g" $PROJ_PATH/app/assets/DayZResources/config.ini
        APK_TARGET=$APK_TARGET_FOLDER/LastShelter_$BUILD_NUMBER-$APP_VERSION_NUMBER-[$curTime]-Release-split.apk
    elif [ "$packagenum" == "0" ]; then
    	sed -i "" "s/FULLAPK=.*/FULLAPK=1/g" $PROJ_PATH/app/assets/DayZResources/config.ini
    	APK_TARGET=$APK_TARGET_FOLDER/LastShelter_$BUILD_NUMBER-$APP_VERSION_NUMBER-[$curTime]-Release-full.apk
    fi
    ./gradlew assembleapk_"$packagenum"Release
    APK_FROM=$PROJ_PATH/app/build/outputs/apk/app-apk_"$packagenum"-release.apk
    cp $APK_FROM $APK_TARGET
done


# push symbol to fabric
./gradlew crashlyticsUploadSymbolsapk_1Release


###


# revert changes
cd $PROJ_PATH
#./gradlew clean
git checkout -- .
#git clean -f