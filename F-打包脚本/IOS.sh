export PATH=$PATH:/usr/local/bin/

if [ "$PACKAGE_FAILED" == "true" ];then
	rm -rf /Users/Shared/Jenkins/git/lastshelter_new_ios/.git/index.lock
    rm -rf /Users/Shared/Jenkins/git/lastshelter_new_ios/.git/modules/lua.update/index.lock
fi

PICVERPATH=/Users/Shared/Jenkins/git
CURRENT_PATH=/Users/Shared/Jenkins/git/lastshelter_new_ios
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
rm -rf text_roe*
cd ../../../
git submodule update

#cd ./lua.update
#git checkout master
#git fetch -p
#git pull 

#xcodebuild -exportArchive -exportOptionsPlist exportPlist.plist -archivePath build/AgainstZ.xcarchive -exportPath "build/store" 
#xcodebuild -exportArchive -exportOptionsPlist exportPlist_adhoc.plist -archivePath build/AgainstZ.xcarchive -exportPath "build/adhoc" 
#exit
security unlock -p "jenkins" ~/Library/Keychains/login2.keychain
#security unlock -p "jenkins" /Users/Shared/Jenkins/Library/Keychains/login2.keychain
security show-keychain-info ~/Library/Keychains/login2.keychain
#security show-keychain-info /Users/Shared/Jenkins/Library/Keychains/login2.keychain
security list-keychains
security default-keychain -s ~/Library/Keychains/login2.keychain
security list-keychains -s ~/Library/Keychains/login2.keychain

GAME_VERSION=$BUILD_NUMBER


#cd CCB
#git checkout  -- .
#if [ "$VERSOIN_FEATURE" == "-" ];then
#  git checkout tilemap_release
#else
#  git checkout tm/r_$VERSOIN_FEATURE
#fi
#git pull


#git submodule update
 

APP_VERSION_NUMBER=$(sed -n "s/.*android:versionName=\"\([0-9\.]*\)\".*/\1/p" Publish.android-studio/WarZ_Google/app/AndroidManifest.xml)

changeIpaBoundId()
{
  rm -rf proj.ios_mac/Images.xcassets/ArabAppIcon.appiconset
  
  #rm -rf -R proj.ios_mac/stickers/Stickers.xcassets/ArabSticker\ Pack.stickerpack/

  #rm -rf -R proj.ios_mac/stickers/Stickers.xcassets/arabiMessage\ App\ Icon.stickersiconset/
}


#处理不需要的arab的资源
changeIpaBoundId

#将扩展包的部分资源放在Resource目录下
sh copyExpack_ios.sh

cd /Users/Shared/Jenkins/git/lastshelter_new_ios/CCB/IF
 #sh pack_ios_zip.sh
cd -    

CreateNewPic() 
{
	echo "CreateNewPic"
	cd /Users/Shared/Jenkins/git/lastshelter_new_ios/CCB/IF
    sh pack_all.sh
    if [ -d "$PICVERPATH/az_ios_pic_ls" ]; then
    	rm -rf "$PICVERPATH/az_ios_pic_ls"
    fi
    mkdir "$PICVERPATH/az_ios_pic_ls"
    cp -r /Users/Shared/Jenkins/git/lastshelter_new_ios/CCB/DayZTexture $PICVERPATH/az_ios_pic_ls/
    if [ -f "$PICVERPATH/az_ios_pic_ver_ls" ]; then
    	rm -rf "$PICVERPATH/az_ios_pic_ver_ls"
    fi
    echo "$PICVER_CURRENT" >> $PICVERPATH/az_ios_pic_ver_ls
}

CopyOldPic()
{
	echo "CopyOldPic"
	if [ -d "/Users/Shared/Jenkins/git/lastshelter_new_ios/CCB/DayZTexture" ]; then
    	rm -rf "/Users/Shared/Jenkins/git/lastshelter_new_ios/CCB/DayZTexture"
    fi
    cp -r "$PICVERPATH/az_ios_pic_ls/DayZTexture" "/Users/Shared/Jenkins/git/lastshelter_new_ios/CCB/"
}

cd CCB/IF
# check pic current version PACKPICTURES
if [ "$PACKPICTURES" == "true" ];then
    CreateNewPic
else
    CopyOldPic
fi
cd ../..


curMonth=`date '+%Y%m'`
curDate=`date '+%Y%m%d'`
curTime=`date '+%H.%M.%S'`

APK_TARGET_FOLDER="/Users/Shared/Jenkins/release/$curMonth/$curDate/LastShelter_iOS_Publish"
if [ ! -d $APK_TARGET_FOLDER ]; then
    mkdir -p $APK_TARGET_FOLDER
fi

# change ipa version
PLIST_FILE="proj.ios_mac/Resources/Info.plist"
/usr/libexec/PlistBuddy -c "Set :CFBundleVersion $GAME_VERSION" $PLIST_FILE
#PLIST_FILE_STICKER="proj.ios_mac/stickers/Info.plist"
#/usr/libexec/PlistBuddy -c "Set :CFBundleVersion $GAME_VERSION" $PLIST_FILE_STICKER
#PLIST_FILE_WATCH="proj.ios_mac/watch/Info.plist"
#/usr/libexec/PlistBuddy -c "Set :CFBundleVersion $GAME_VERSION" $PLIST_FILE_WATCH
#PLIST_FILE_WATCH_EXTENSION="proj.ios_mac/watch Extension/Info.plist"
#/usr/libexec/PlistBuddy -c "Set :CFBundleVersion $GAME_VERSION" "$PLIST_FILE_WATCH_EXTENSION"
PLIST_FILE_TODAY_EXTENSION="proj.ios_mac/AgainstZ Extension/Info.plist"
/usr/libexec/PlistBuddy -c "Set :CFBundleVersion $GAME_VERSION" "$PLIST_FILE_TODAY_EXTENSION"
#AgainstZ Notification
PLIST_FILE_NOTIFICATION="proj.ios_mac/AgainstZNS/Info.plist"
/usr/libexec/PlistBuddy -c "Set :CFBundleVersion $GAME_VERSION" "$PLIST_FILE_NOTIFICATION"
#AgainstZ Notification Content
PLIST_FILE_NOTIFICATION_CONTENT="proj.ios_mac/AgainstZNC/Info.plist"
/usr/libexec/PlistBuddy -c "Set :CFBundleVersion $GAME_VERSION" "$PLIST_FILE_NOTIFICATION_CONTENT"

# /usr/libexec/PlistBuddy -c "Set :CFBundleShortVersionString $GAME_VERSION" $PLIST_FILE

rm -rf -R build/

# archive and export ipa
xcodebuild -scheme AgainstZ -project proj.ios_mac/FreeBuild.xcodeproj -configuration Release clean archive -archivePath build/AgainstZ.xcarchive -hideShellScriptEnvironment | egrep -A 5 "(error|warning):" 
#p /Users/Shared/Jenkins/git/Assets.car build/AgainstZ.xcarchive/Products/Applications/AgainstZ.app/PlugIns/stickers.appex/Assets.car
#echo "cp Assets.car Done!"
xcodebuild -exportArchive -exportOptionsPlist exportPlist.plist -archivePath build/AgainstZ.xcarchive -exportPath "build/store" 
#测试adhoc
xcodebuild -exportArchive -exportOptionsPlist exportPlist_adhoc.plist -archivePath build/AgainstZ.xcarchive -exportPath "build/adhoc" 
#xcodebuild -exportArchive -exportFormat ipa -archivePath "build/AgainstZ.xcarchive" -exportPath "build/AgainstZ_dis.ipa" -exportProvisioningProfile "AgainstZ_store" -hideShellScriptEnvironment | egrep -A 5 "(error|warning):"
#xcodebuild -exportArchive -exportFormat ipa -archivePath "build/AgainstZ.xcarchive" -exportPath "build/AgainstZ_hoc.ipa" -exportProvisioningProfile "AgainstZ_adhoc" -hideShellScriptEnvironment | egrep -A 5 "(error|warning):"

DIS_HASH_NUM=` shasum build/store/AgainstZ.ipa | awk '{print $1}' `
HOC_HASH_NUM=` shasum build/adhoc/AgainstZ.ipa | awk '{print $1}' `


cp build/store/AgainstZ.ipa $APK_TARGET_FOLDER/AgainstZ-ios-$curTime-$BUILD_NUMBER-$APP_VERSION_NUMBER-$GAME_VERSION-V3.ipa
#测试adhoc
cp build/adhoc/AgainstZ.ipa $APK_TARGET_FOLDER/AgainstZ-ios-$curTime-$BUILD_NUMBER-$APP_VERSION_NUMBER-$GAME_VERSION-adhoc-V3.ipa
cp -R build/AgainstZ.xcarchive $APK_TARGET_FOLDER/AgainstZ-ios-$curTime-$BUILD_NUMBER-$APP_VERSION_NUMBER_$GAME_VERSION-AgainstZ.xcarchive


#删除放到Resource目录下的扩展包
rm -rf $CURRENT_PATH/CCB/DayZTexture/android_expack


git checkout -- .

{
	/Users/macpro/Desktop/Fabric.app/Contents/MacOS/upload-symbols -a ee8bb31e17f323c2ce0c6da836e1b96fa7318858 -p ios build/AgainstZ.xcarchive/dSYMs/AgainstZ.app.dSYM
}
{
	cp -R build/AgainstZ.xcarchive/dSYMs/AgainstZ.app.dSYM build/AgainstZ.app.dSYM
    /Users/macpro/Desktop/Fabric.app/Contents/MacOS/upload-symbols -a ee8bb31e17f323c2ce0c6da836e1b96fa7318858 -p ios build/AgainstZ.app.dSYM
	echo ">>>> Bugly upload begin"
    #Bugly upload dSYM file
  	#sh $CURRENT_PATH/dSYMUpload.sh "833dcd3d1a" "2eab3955-02b7-4525-85f2-92d5be7c0ce2" "com.im30.warz" $GAME_VERSION $build $build/BuglyZipTemp "1"
	echo ">>>> Bugly upload end"
}
