## 在 iOS 上使用 COS C++ SDK

### 运行示例

#### 1. 下载已编译好的静态库

[boost](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/iOS/boost.zip)

[poco](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/iOS/poco.zip)

[openssl](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/iOS/openssl.zip)

[cos-sdk](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/iOS/cos.zip)

所有静态库都支持 arm64, x86_64。

#### 2. 运行示例工程

示例工程在 demo/example-cos-app 下。 

将下载的静态库解压放在 `libs` 文件夹下，用 xcode 打开即可运行。

### 如何编译

#### 1. 编译 openssl

参考 [openssl_for_ios_and_android](https://github.com/leenjewel/openssl_for_ios_and_android.git)

将编译好的 lib 放置于 libs/openssl

#### 2. 编译 boost

参考 [Apple-Boost-BuildScript](https://github.com/faithfracture/Apple-Boost-BuildScript)

```shell script
./boost.sh -ios
```

将编译好的 framework 放置于 libs/boost

#### 3. 编译 poco

下载 [poco 源码](https://github.com/pocoproject/poco)

下载 [编译脚本](https://github.com/konakonall/Poco)

```shell script
./build.sh 1.10.1 9.0 iOS CLEAN
```

将编译好的 framework 放置于 libs/poco

#### 4. 编译 COS SDK

toolchain 的用法请参考 [ios-cmake](https://github.com/leetal/ios-cmake)

```shell script
./build_ios.sh
```
