## 在 iOS 上使用 COS C++ SDK

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

参考 [Apple-Boost-BuildScript](https://github.com/faithfracture/Apple-Boost-BuildScript)

```shell script
./boost.sh -ios
```

将编译好的 framework 放置于 libs/boost

#### 3. 编译 poco

下载 [poco 源码](https://github.com/pocoproject/poco)

下载 [编译脚本](https://github.com/konakonall/Poco)

```shell script
# 用法
./build_ios.sh $iOS_VERSION $POCO_REPO_ROOT_DIR

# 例如
./build_ios.sh 9.0 ~/Workspace/libs/poco

# 最终打包产物在 $PWD/Build/iOS 下
```

将编译好的 framework 放置于 libs/poco

#### 4. 编译 COS SDK

toolchain 的用法请参考 [ios-cmake](https://github.com/leetal/ios-cmake)

```shell script
./build_ios.sh
```

### 运行示例

示例工程在 demo/example-ios-app 下。 

1. 将所有的静态库解压放在 `libs` 文件夹下
2. SDK 运行需要一个配置文件，在 `example-cos-app/config.json` 中填入你的密钥。
3. 用 xcode 打开即可运行。


