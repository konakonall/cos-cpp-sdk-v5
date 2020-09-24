#include <jni.h>
#include <string>
#include "cos.hpp"
#include <android/log.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "logger.hpp"

extern "C" JNIEXPORT jstring JNICALL
Java_com_tencent_cloud_cos_example_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    cos_start_logger("cos_test");

    std::string config = "/data/data/com.tencent.cloud.cos.example/files/config.json";
    std::ifstream ifs(config.c_str(), std::ios::in);
    std::cout << "is_open = " << ifs.is_open() << std::endl;

    std::string cacheFile = "/data/data/com.tencent.cloud.cos.example/cache/temp";
    getService(config);
    getObject(config, cacheFile);
    putObject(config, cacheFile);

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
