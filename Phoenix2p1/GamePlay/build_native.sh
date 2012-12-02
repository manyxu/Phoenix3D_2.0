#!/bin/bash
# set params
NDK_ROOT_LOCAL=/cygdrive/d/android/android-ndk
PX2_ROOT_LOCAL=/cygdrive/e/Phoenix3d/Phoenix2p1

# set roots
if [ $NDK_ROOT"xyz" != "xyz" ]; then
	echo "use global definition of NDK_ROOT: $NDK_ROOT"
	NDK_ROOT_LOCAL=$NDK_ROOT
fi

if [ $PX2_ROOT"xyz" != "xyz" ]; then
	echo "use global definition of PX2_ROOT: $PX2_ROOT"
	PX2_ROOT_LOCAL=$PX2_ROOT
fi

GAMEPLAY_ANDROID_ROOT=$PX2_ROOT_LOCAL/GamePlay/Proj.Android

# make sure assets is exist
if [ -d $GAMEPLAY_ANDROID_ROOT/assets ]; then
	rm -rf $GAMEPLAY_ANDROID_ROOT/assets
fi

mkdir $GAMEPLAY_ANDROID_ROOT/assets

# copy resources

# build
echo "start build"

export NDK_MODULE_PATH=$PX2_ROOT_LOCAL\
:$PX2_ROOT_LOCAL/PX2Core/\
:$PX2_ROOT_LOCAL/PX2Mathematics/\
:$PX2_ROOT_LOCAL/PX2Graphics/\
:$PX2_ROOT_LOCAL/PX2EventSystem/\
:$PX2_ROOT_LOCAL/PX2Unity/\
:$PX2_ROOT_LOCAL/PX2Game/\
:$PX2_ROOT_LOCAL/PX2AppFrame/\
:$PX2_ROOT_LOCAL/GamePlay/\
:$GAMEPLAY_ANDROID_ROOT

$NDK_ROOT_LOCAL/ndk-build -C $GAMEPLAY_ANDROID_ROOT

echo "end build"