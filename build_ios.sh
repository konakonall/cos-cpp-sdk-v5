#!/bin/sh

OPENSSL_HOME=$PWD/libs/openssl

RELEASE_DIR=$PWD/build/release
X86_64_DIR=$PWD/build/x86_64
ARM64_DIR=$PWD/build/arm64

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

xcrun -sdk iphoneos lipo \
-create \
-arch x86_64 "${X86_64_DIR}/lib/Release/libcossdk.a" \
-arch arm64 "${ARM64_DIR}/lib/Release/libcossdk.a" \
-o "${RELEASE_DIR}/libcossdk.a" \
|| abort "Lipo $1 failed"

ranlib "${RELEASE_DIR}/libcossdk.a"
