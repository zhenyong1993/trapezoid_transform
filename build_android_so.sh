#!/bin/sh
# set -x
set -e

# 1. 安装cmake
# 2. 安装NDK（可利用android studio安装）

abis=("arm64-v8a" "armeabi-v7a" "x86")
toolchains=("aarch64-linux-android" "arm-linux-androideabi" "i686-linux-android")	# 参考$ndk_path/build/cmake/android.toolchain.cmake
ndk_path=$HOME/Android/Sdk/ndk/21.4.7075529

android_out_dir="android-out"

include_files=("MaxInnerRect.h") # include_files表示需要发布的头文件，会被拷贝到build-out目录中，路径为相对于本脚本的路径或绝对路径
dest_libs=("libmax_inner_rect.so") # dest_libs表示需要发布的库文件，会分别将各abi的库拷贝到build-out目录的相应目录中

for ((i=0;i<${#abis[@]};i++)) do
  if [ ! -e build-${abis[i]} ]; then
    mkdir build-${abis[i]}
  fi
  cd build-${abis[i]}

  for ((j=0;j<${#dest_libs[@]};j++)) do
    if [ -e ${dest_libs[j]} ]; then
      rm ${dest_libs[j]}
    fi
  done

  # 参考https://developer.android.com/studio/projects/configure-cmake?hl=zh-cn
  # ANDROID_PLATFORM的值可保持和调用该so的安卓代码中设置的"compileSdkVersion"一致
  # 在使用的ANDROID_NDK(此处为$ndk_path)的platforms文件夹中可以看到该ndk支持的安卓API LEVEL，需要保证该ndk支持的API LEVEL可以覆盖minSdkVersion到compileSdkVersion
  # 任意参数表示编译debug版本并且不strip
  if [ $# -ne 1 ]; then
    cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI=${abis[i]} -DANDROID_STL=c++_static -DANDROID_PLATFORM=android-30 -DANDROID_NDK=$ndk_path -DCMAKE_TOOLCHAIN_FILE=$ndk_path/build/cmake/android.toolchain.cmake ..
  else
    cmake -DCMAKE_BUILD_TYPE=Debug -DANDROID_ABI=${abis[i]} -DANDROID_STL=c++_static -DANDROID_PLATFORM=android-30 -DANDROID_NDK=$ndk_path -DCMAKE_TOOLCHAIN_FILE=$ndk_path/build/cmake/android.toolchain.cmake ..
  fi
  make -j8

  if [ $# -ne 1 ]; then
    for ((j=0;j<${#dest_libs[@]};j++)) do
      $ndk_path/toolchains/llvm/prebuilt/linux-x86_64/bin/${toolchains[i]}-strip ${dest_libs[j]}
    done
  fi

  cd ..
done

if [ -e $android_out_dir ]; then
  rm -rf $android_out_dir
fi

mkdir $android_out_dir
for ((i=0;i<${#include_files[@]};i++)) do
  cp ${include_files[i]} $android_out_dir/
done

for ((i=0;i<${#abis[@]};i++)) do
  mkdir $android_out_dir/${abis[i]}

  for ((j=0;j<${#dest_libs[@]};j++)) do
    cp build-${abis[i]}/${dest_libs[j]} $android_out_dir/${abis[i]}/
  done
  
done
