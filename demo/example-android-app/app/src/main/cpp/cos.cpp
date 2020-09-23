//
//  cos.cpp
//  example-cos-app
//
//  Created by wjielai on 2020/9/17.
//

#include "cos.hpp"
#include <cos_api.h>
#include <cos_sys_config.h>
#include <cos_defines.h>
#include <stdio.h>

static std::string bucketName = "000000-1253653367";

void getService(std::string configFilePath) {
    // 1. 指定配置文件路径，初始化 CosConfig
    qcloud_cos::CosConfig config(configFilePath);
    qcloud_cos::CosAPI cos(config);

    // 2. 构造查询存储桶列表的请求
    qcloud_cos::GetServiceReq req;
    qcloud_cos::GetServiceResp resp;
    qcloud_cos::CosResult result = cos.GetService(req, &resp);

    // 3. 获取响应信息
    const qcloud_cos::Owner& owner = resp.GetOwner();
    const std::vector<qcloud_cos::Bucket>& buckets = resp.GetBuckets();
    std::cout << "owner.m_id=" << owner.m_id << ", owner.display_name=" << owner.m_display_name << std::endl;

    for (std::vector<qcloud_cos::Bucket>::const_iterator itr = buckets.begin(); itr != buckets.end(); ++itr) {
        const qcloud_cos::Bucket& bucket = *itr;
        std::cout << "Bucket name=" << bucket.m_name << ", location="
            << bucket.m_location << ", create_date=" << bucket.m_create_date << std::endl;
    }

    // 4. 处理调用结果
    if (result.IsSucc()) {
        // 查询存储桶列表成功
    } else {
        // 查询存储桶列表失败，可以调用 CosResult 的成员函数输出错误信息，比如 requestID 等
        std::cout << "ErrorInfo=" << result.GetErrorInfo() << std::endl;
        std::cout << "HttpStatus=" << result.GetHttpStatus() << std::endl;
        std::cout << "ErrorCode=" << result.GetErrorCode() << std::endl;
        std::cout << "ErrorMsg=" << result.GetErrorMsg() << std::endl;
        std::cout << "ResourceAddr=" << result.GetResourceAddr() << std::endl;
        std::cout << "XCosRequestId=" << result.GetXCosRequestId() << std::endl;
        std::cout << "XCosTraceId=" << result.GetXCosTraceId() << std::endl;
    }
}

void getObject(std::string configFilePath, std::string localFilePath) {
    // 1. 指定配置文件路径，初始化 CosConfig
    qcloud_cos::CosConfig config(configFilePath);
    qcloud_cos::CosAPI cos(config);

    // 2. 构造下载对象的请求
    std::string bucket_name = bucketName; // 上传的目的 Bucket 名称
    std::string object_name = "exampleobject"; // exampleobject 即为对象键（Key），是对象在存储桶中的唯一标识。例如，在对象的访问域名 examplebucket-1250000000.cos.ap-guangzhou.myqcloud.com/doc/pic.jpg 中，对象键为 doc/pic.jpg。
    std::string local_path = localFilePath;
    // request 需要提供 appid、bucketname、object,以及本地的路径（包含文件名）
    qcloud_cos::GetObjectByFileReq req(bucket_name, object_name, local_path);
    qcloud_cos::GetObjectByFileResp resp;

    // 3. 调用下载对象接口
    qcloud_cos::CosResult result = cos.GetObject(req, &resp);

    // 4. 处理调用结果
    if (result.IsSucc()) {
        // 下载文件成功
    } else {
        // 下载文件失败，可以调用 CosResult 的成员函数输出错误信息，例如 requestID 等
        std::cout << "ErrorInfo=" << result.GetErrorInfo() << std::endl;
        std::cout << "HttpStatus=" << result.GetHttpStatus() << std::endl;
        std::cout << "ErrorCode=" << result.GetErrorCode() << std::endl;
        std::cout << "ErrorMsg=" << result.GetErrorMsg() << std::endl;
        std::cout << "ResourceAddr=" << result.GetResourceAddr() << std::endl;
        std::cout << "XCosRequestId=" << result.GetXCosRequestId() << std::endl;
        std::cout << "XCosTraceId=" << result.GetXCosTraceId() << std::endl;
    }
}

void putObject(std::string configFilePath, std::string localFilePath) {
    // 1. 指定配置文件路径，初始化 CosConfig
    qcloud_cos::CosConfig config(configFilePath);
    qcloud_cos::CosAPI cos(config);

    // 2. 构造上传文件的请求
    std::string bucket_name = bucketName; // 上传的目的 Bucket 名称
    std::string object_name = "exampleobject_upload"; //exampleobject 即为对象键（Key），是对象在存储桶中的唯一标识。例如，在对象的访问域名 examplebucket-1250000000.cos.ap-guangzhou.myqcloud.com/doc/pic.jpg 中，对象键为 doc/pic.jpg。
    // request 的构造函数中需要传入本地文件路径
    qcloud_cos::PutObjectByFileReq req(bucket_name, object_name, localFilePath);
    qcloud_cos::PutObjectByFileResp resp;

    // 3. 调用上传文件接口
    qcloud_cos::CosResult result = cos.PutObject(req, &resp);

    // 4. 处理调用结果
    if (result.IsSucc()) {
        // 上传文件成功
    } else {
        // 上传文件失败，可以调用 CosResult 的成员函数输出错误信息，比如 requestID 等
        std::cout << "ErrorInfo=" << result.GetErrorInfo() << std::endl;
        std::cout << "HttpStatus=" << result.GetHttpStatus() << std::endl;
        std::cout << "ErrorCode=" << result.GetErrorCode() << std::endl;
        std::cout << "ErrorMsg=" << result.GetErrorMsg() << std::endl;
        std::cout << "ResourceAddr=" << result.GetResourceAddr() << std::endl;
        std::cout << "XCosRequestId=" << result.GetXCosRequestId() << std::endl;
        std::cout << "XCosTraceId=" << result.GetXCosTraceId() << std::endl;
    }
}
