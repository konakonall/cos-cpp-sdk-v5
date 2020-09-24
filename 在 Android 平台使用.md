## 在 Android 上使用 COS C++ SDK

### 依赖

COS SDK 依赖于如下开源库

* [boost](https://www.boost.org/)
* [poco](https://pocoproject.org/)
* [openssl](https://github.com/openssl/openssl)

您可以使用已编译好的静态库，也可以自己编译。

### 使用预编译的静态库

下面提供了已编译好的静态库，所有静态库都支持 armeabi-v7a, arm64-v8a, x86, x86_64。

[boost](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/Android/boost.zip)

[poco](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/Android/poco.zip)

[openssl](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/Android/openssl.zip)

[cos-sdk](https://cos-sdk-archive-1253960454.cos.ap-guangzhou.myqcloud.com/cos-cpp-sdk-binary/Android/cos.zip)

### 手动编译

#### 1. 编译 openssl

参考 [openssl_for_ios_and_android](https://github.com/leenjewel/openssl_for_ios_and_android.git)

将编译好的 lib 放置于 libs/openssl

#### 2. 编译 boost

参考 [Boost-for-Android](https://github.com/moritz-wundke/Boost-for-Android)

```shell script
./build-android.sh $(NDK_ROOT)
```

将编译好的 lib 放置于 libs/boost

#### 3. 编译 poco

下载 [poco 源码](https://github.com/pocoproject/poco)

下载 [编译脚本](https://github.com/konakonall/Poco)

```shell script
# 使用方法
./build_android.sh $ANDROID_CMAKE_HOME $POCO_REPO_ROOT_DIR $OPENSSL_ROOT_DIR

# 例如
./build_android.sh ～/Library/Android/sdk/cmake/3.10.2.4988404 / 
~/Workspace/libs/poco /
~/Workspace/cos-sdk-repos/cos-cpp-sdk-v5/libs/openssl

# 最终打包产物在 $PWD/Build/Android 下
```

将编译好的 lib 放置于 libs/poco

#### 4. 编译 COS SDK

```shell script
./build_android.sh
```

### 运行示例

示例工程在 demo/example-android-app 下。 

1. 将所有的静态库解压放在 `app/src/main/cpp/libs` 文件夹下
2. SDK 运行需要一个配置文件，参考 `example-android-app/config.json`，在测试机/模拟器中创建好配置文件。demo 默认从路径 `/data/data/com.tencent.cloud.cos.example/files/config.json` 读取。
3. 用 Android Studio 打开运行。


