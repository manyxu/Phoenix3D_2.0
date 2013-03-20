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

# assets
if [ -d $GAMEPLAY_ANDROID_ROOT/assets ]; then
	rm -rf $GAMEPLAY_ANDROID_ROOT/assets
fi

mkdir $GAMEPLAY_ANDROID_ROOT/assets
mkdir $GAMEPLAY_ANDROID_ROOT/assets/Data
mkdir $GAMEPLAY_ANDROID_ROOT/assets/Data/fonts
mkdir $GAMEPLAY_ANDROID_ROOT/assets/Data/language
mkdir $GAMEPLAY_ANDROID_ROOT/assets/Data/projects
mkdir $GAMEPLAY_ANDROID_ROOT/assets/Data/scenes
mkdir $GAMEPLAY_ANDROID_ROOT/assets/Data/scripts

cp -rf $PX2_ROOT_LOCAL/Bin/Data/boost.lua $GAMEPLAY_ANDROID_ROOT/assets/Data
cp -rf $PX2_ROOT_LOCAL/Bin/Data/boost.xml $GAMEPLAY_ANDROID_ROOT/assets/Data

for file in $PX2_ROOT_LOCAL/Bin/Data/fonts/*
do
if [ -d $file ]; then
cp -rf $file $GAMEPLAY_ANDROID_ROOT/assets/Data/fonts
fi
if [ -f $file ]; then
cp $file $GAMEPLAY_ANDROID_ROOT/assets/Data/fonts
fi
done

for file in $PX2_ROOT_LOCAL/Bin/Data/language/*
do
if [ -d $file ]; then
cp -rf $file $GAMEPLAY_ANDROID_ROOT/assets/Data/language
fi
if [ -f $file ]; then
cp $file $GAMEPLAY_ANDROID_ROOT/assets/Data/language
fi
done

for file in $PX2_ROOT_LOCAL/Bin/Data/projects/*
do
if [ -d $file ]; then
cp -rf $file $GAMEPLAY_ANDROID_ROOT/assets/Data/projects
fi
if [ -f $file ]; then
cp $file $GAMEPLAY_ANDROID_ROOT/assets/Data/projects
fi
done

for file in $PX2_ROOT_LOCAL/Bin/Data/scenes/*
do
if [ -d $file ]; then
cp -rf $file $GAMEPLAY_ANDROID_ROOT/assets/Data/scenes
fi
if [ -f $file ]; then
cp $file $GAMEPLAY_ANDROID_ROOT/assets/Data/scenes
fi
done

for file in $PX2_ROOT_LOCAL/Bin/Data/scripts/*
do
if [ -d $file ]; then
cp -rf $file $GAMEPLAY_ANDROID_ROOT/assets/Data/scripts
fi
if [ -f $file ]; then
cp $file $GAMEPLAY_ANDROID_ROOT/assets/Data/scripts
fi
done

# copy resources

# build
echo "start build"

export NDK_MODULE_PATH=$PX2_ROOT_LOCAL\
:$PX2_ROOT_LOCAL/PX2Core/\
:$PX2_ROOT_LOCAL/PX2Mathematics/\
:$PX2_ROOT_LOCAL/PX2Graphics/\
:$PX2_ROOT_LOCAL/PX2EventSystem/\
:$PX2_ROOT_LOCAL/PX2Input/\
:$PX2_ROOT_LOCAL/PX2Unity/\
:$PX2_ROOT_LOCAL/PX2Terrains/\
:$PX2_ROOT_LOCAL/PX2Effect/\
:$PX2_ROOT_LOCAL/PX2UserInterface/\
:$PX2_ROOT_LOCAL/PX2Game/\
:$PX2_ROOT_LOCAL/PX2AppFrame/\
:$PX2_ROOT_LOCAL/GamePlay/\
:$GAMEPLAY_ANDROID_ROOT

$NDK_ROOT_LOCAL/ndk-build -C $GAMEPLAY_ANDROID_ROOT

echo "end build"