#include <helios_service.h>

namespace helios {

int HeliosServiceImpl::listBuckets (Client& client) {
    //获取用户的Bucket列表
    ListBucketsRequest listBucketsRequest;
    ListBucketsResponse listBucketsResponse;
    int ret = client.list_buckets(listBucketsRequest, &listBucketsResponse);
    std::vector<BucketSummary> bucketSummaryList = listBucketsResponse.buckets();
    if (listBucketsResponse.is_fail()) {
        printf("error-message:%s\n", listBucketsResponse.error().message().c_str());
        return ret;
    }
    //遍历Bucket
    for(const BucketSummary& bs : bucketSummaryList){
        std::cout << "bucketName: " << bs.name <<  std::endl;
    }
    return ret;
}

void HeliosServiceImpl::emoji(::google::protobuf::RpcController* controller,
       const helios::EmojiReq* req,
       helios::EmojiResp* resp,
       ::google::protobuf::Closure* done)
{
    FILE *logfp = fopen("log/sdk.log", "w");
    sdk_set_log_stream(logfp);
    sdk_set_log_level(SDK_LOG_DEBUG);

    baidu::bos::cppsdk::Client client(ACCESS_KEY_ID, SECRET_ACCESS_KEY);
    listBuckets(client);

    done->Run();
}

}
