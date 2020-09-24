#!/bin/sh

if [ -z $ANDROID_HOME ]; then
    echo "Please set ANDROID_HOME in environment."
    exit 1
fi

OPENSSL_HOME=$PWD/libs/openssl

CURRENT_DIR=$PWD
BUILD_DIR=$CURRENT_DIR/temp
RELEASE_DIR=$PWD/build/Android

rm -fr $RELEASE_DIR
mkdir -p $RELEASE_DIR

for ABI in {x86_64,x86,armeabi-v7a,arm64-v8a}
do
  rm -fr $BUILD_DIR
  mkdir -p $BUILD_DIR
  cd $BUILD_DIR

  cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=$ANDROID_HOME/ndk-bundle/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=$ABI \
    -DANDROID_NATIVE_API_LEVEL=23 \
    -DANDROID=1 \
    -DANDROID_STL=c++_shared \
    -DOPENSSL_INCLUDE_DIR=$OPENSSL_HOME/include \
    -DOPENSSL_CRYPTO_LIBRARY=$OPENSSL_HOME/libcrypto.a \
    -DOPENSSL_SSL_LIBRARY=$OPENSSL_HOME/libssl.a

  cmake --build . --config Release --target cossdk

  mkdir -p $RELEASE_DIR/$ABI
  cp -r $BUILD_DIR/lib/* $RELEASE_DIR/$ABI
done

mkdir $RELEASE_DIR/include
cp -r $CURRENT_DIR/include/* $RELEASE_DIR/include

rm -fr $BUILD_DIR

echo "Build Complete"
