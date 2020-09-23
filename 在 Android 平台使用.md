## 在 Android 上使用 COS C++ SDK

### 依赖

COS SDK 依赖于如下开源库

* [boost](https://www.boost.org/)
* [poco](https://pocoproject.org/)
* [openssl](https://github.com/openssl/openssl)

您可以使用已编译好的静态库，也可以自己编译。

### 使用预编译的静态库

下面提供了已编译好的静态库，所有静态库都支持 arm64, x86_64。

[boost](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/iOS/boost.zip)

[poco](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/iOS/poco.zip)

[openssl](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/iOS/openssl.zip)

[cos-sdk](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/iOS/cos.zip)

### 手动编译

#### 1. 编译 openssl

参考 [openssl_for_ios_and_android](https://github.com/leenjewel/openssl_for_ios_and_android.git)

将编译好的 lib 放置于 libs/openssl

#### 2. 编译 boost

参考 [Boost-for-Android](https://github.com/moritz-wundke/Boost-for-Android)

```shell script
./build-android.sh $(NDK_ROOT)
```

将编译好的 framework 放置于 libs/boost

#### 3. 编译 poco

下载 [poco 源码](https://github.com/pocoproject/poco)

下载 [编译脚本](https://github.com/konakonall/Poco)

```shell script
/Users/wjielai/Library/Android/sdk/cmake/3.10.2.4988404/bin/cmake -H. \ 
-B/tmp/poco-build -G'Ninja' \
-DCMAKE_BUILD_TYPE=Release \ 
-DCMAKE_MAKE_PROGRAM=/Users/wjielai/Library/Android/sdk/cmake/3.10.2.4988404/bin/ninja \ 
-DCMAKE_TOOLCHAIN_FILE=/Users/wjielai/Library/Android/sdk/ndk-bundle/build/cmake/android.toolchain.cmake \ 
-DANDROID_NATIVE_API_LEVEL=24 \ 
-DANDROID_ABI=x86_64  \ 
-DOPENSSL_INCLUDE_DIR=/Users/wjielai/Workspace/cos-sdk-repos/cos-cpp-sdk-v5/libs/openssl/include  \ 
-DOPENSSL_CRYPTO_LIBRARY=/Users/wjielai/Workspace/cos-sdk-repos/cos-cpp-sdk-v5/libs/openssl/x86_64/libcrypto.a  \ 
-DOPENSSL_SSL_LIBRARY=/Users/wjielai/Workspace/cos-sdk-repos/cos-cpp-sdk-v5/libs/openssl/x86_64/libssl.a  \ 
-DENABLE_NETSSL=1  \ 
-DENABLE_DATA_SQLITE=0 \ 
-DENABLE_MONGODB=0  \
-DENABLE_ENCODINGS=0 \
-DENABLE_REDIS=0 \ 
-DENABLE_JWT=0 \
-DENABLE_ZIP=0 \
-DENABLE_PAGECOMPILER=0 \
-DENABLE_PAGECOMPILER_FILE2PAGE=0


/Users/wjielai/Library/Android/sdk/cmake/3.10.2.4988404/bin/cmake --build /tmp/poco-build
```

将编译好的 framework 放置于 libs/poco

#### 4. 编译 COS SDK

```shell script
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=/Users/wjielai/Library/Android/sdk/ndk-bundle/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=x86_64 \
    -DANDROID_NATIVE_API_LEVEL=24 \
    -DANDROID=1 \
    -DANDROID_STL=c++_shared \
    -DOPENSSL_INCLUDE_DIR=/Users/wjielai/Workspace/cos-sdk-repos/cos-cpp-sdk-v5/libs/openssl/include \
    -DOPENSSL_CRYPTO_LIBRARY=/Users/wjielai/Workspace/cos-sdk-repos/cos-cpp-sdk-v5/libs/openssl/x86_64/libcrypto.a \
    -DOPENSSL_SSL_LIBRARY=/Users/wjielai/Workspace/cos-sdk-repos/cos-cpp-sdk-v5/libs/openssl/x86_64/libssl.a

cmake --build . --config Release --target cossdk
```

### 运行示例

示例工程在 demo/example-android-app 下。 

将所有的静态库解压放在 `libs` 文件夹下，用 xcode 打开即可运行。


