#!/bin/sh

OPENSSL_HOME=$PWD/libs/openssl

CURRENT_DIR=$PWD
RELEASE_DIR=$CURRENT_DIR/build/iOS
X86_64_DIR=$CURRENT_DIR/temp/x86_64
ARM64_DIR=$CURRENT_DIR/temp/arm64

rm -fr $RELEASE_DIR
mkdir -p $RELEASE_DIR

rm -fr $ARM64_DIR
mkdir -p $ARM64_DIR
cd $ARM64_DIR
cmake ../.. -G Xcode -DCMAKE_TOOLCHAIN_FILE=../../ios.toolchain.cmake -DPLATFORM=OS64COMBINED -DIOS=1 -DOPENSSL_ROOT_DIR=$OPENSSL_HOME
cmake --build . --config Release --target cossdk

rm -fr $X86_64_DIR
mkdir -p $X86_64_DIR
cd $X86_64_DIR
cmake ../.. -G Xcode -DCMAKE_TOOLCHAIN_FILE=../../ios.toolchain.cmake -DPLATFORM=SIMULATOR64 -DIOS=1 -DOPENSSL_ROOT_DIR=$OPENSSL_HOME
cmake --build . --config Release --target cossdk

mkdir -p $RELEASE_DIR/lib

xcrun -sdk iphoneos lipo \
-create \
-arch x86_64 "${X86_64_DIR}/lib/Release/libcossdk.a" \
-arch arm64 "${ARM64_DIR}/lib/Release/libcossdk.a" \
-o "${RELEASE_DIR}/lib/libcossdk.a" \
|| abort "Lipo $1 failed"

ranlib "${RELEASE_DIR}/libcossdk.a"

mkdir $RELEASE_DIR/include
cp -r $CURRENT_DIR/include/* $RELEASE_DIR/include

rm -fr $X86_64_DIR
rm -fr $ARM64_DIR

echo "Build Complete"
