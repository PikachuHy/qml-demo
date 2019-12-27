//
// Created by PikachuHy on 2019/12/17.
//
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <memory>
#include <alibabacloud/oss/OssClient.h>
using namespace AlibabaCloud::OSS;
using std::string;
void PrintError(const std::string &funcName, const OssError &error)
{
    std::cout << funcName << " fail" <<
              ",code:" << error.Code() <<
              ",message:" << error.Message() <<
              ",request_id:" << error.RequestId() << std::endl;
}

int main(int argc, char** argv)
{
    // 初始化SDK
    InitializeSdk();

    // 配置实例
    ClientConfiguration conf;
    OssClient client("http://oss-cn-hangzhou.aliyuncs.com",
            "<>",
            "<>", conf);
    string bucket = "nls-demo";
    string filepath = "/Users/pikachu/Desktop/QQ20191217-104133@2x.png";
    auto outcome = client.PutObject(bucket, "test.png", filepath);
    if (!outcome.isSuccess()) {
        /* 异常处理 */
        std::cout << "PutObject fail" <<
                  ",code:" << outcome.error().Code() <<
                  ",message:" << outcome.error().Message() <<
                  ",requestId:" << outcome.error().RequestId() << std::endl;
        ShutdownSdk();
        return -1;
    }
    std::cout << outcome.result().Content();
    /*
    // 创建API请求
    ListBucketsRequest request;
    auto outcome = client.ListBuckets(request);
    if (!outcome.isSuccess()) {
        // 异常处理
        std::cout << "ListBuckets fail" <<
                  ",code:" << outcome.error().Code() <<
                  ",message:" << outcome.error().Message() <<
                  ",requestId:" << outcome.error().RequestId() << std::endl;
        ShutdownSdk();
        return -1;
    }
    */
/*
    string bucket_ = "nls-demo";
    std::shared_ptr<std::iostream> content = std::make_shared<std::fstream>(__FILE__, std::ios::in);
    PutObjectRequest request(bucket_, "PutObjectFromFile", content);
    auto outcome = client.PutObject(request);
    if (outcome.isSuccess()) {
        std::cout << __FUNCTION__ << " success, ETag:" << outcome.result().ETag() << std::endl;
    }
    else {
        PrintError(__FUNCTION__, outcome.error());
    }
    */
    std::cout << "Done" << std::endl;
    // 关闭SDK
    ShutdownSdk();
    return 0;
}