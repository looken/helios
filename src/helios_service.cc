#include <helios_service.h>

#include <utils/base64.h>
#include <utils/md5.h>

using namespace sofa::pbrpc;

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

void HeliosServiceImpl::base64_encode(::google::protobuf::RpcController* controller,
                                      const helios::Base64EncodeReq* req,
                                      helios::Base64EncodeResp* resp,
                                      ::google::protobuf::Closure* done)
{
    std::string data(req->data());
    std::string base64_data(utils::base64_encode(data.c_str(), data.size()));
    resp->set_data_base64(base64_data);
    done->Run();
}

void HeliosServiceImpl::base64_decode(::google::protobuf::RpcController* controller,
                                      const helios::Base64DecodeReq* req,
                                      helios::Base64DecodeResp* resp,
                                      ::google::protobuf::Closure* done)
{
    std::string data_base64(req->data_base64());
    std::string data = utils::base64_decode(data_base64.c_str(), data_base64.size());
    resp->set_data(data);
    done->Run();
}

void HeliosServiceImpl::md5_encode(::google::protobuf::RpcController* controller,
                                   const helios::Md5EncodeReq* req,
                                   helios::Md5EncodeResp* resp,
                                   ::google::protobuf::Closure* done)
{
    std::string data(req->data());
    char md5str[33];
    utils::md5(data.c_str(), data.size() + 1, md5str);
    resp->set_data_md5(md5str);
    done->Run();
}

void HeliosServiceImpl::background_image(::google::protobuf::RpcController* controller,
                                         const helios::BackgroundImageReq* req,
                                         helios::BackgroundImageResp* resp,
                                         ::google::protobuf::Closure* done)
{
    ListObjectsRequest listObjectsRequest(STARS_BUCKET);
    std::stringstream prefix;
    prefix << "background-image/" << req->key();
    listObjectsRequest.set_prefix(prefix.str().c_str());
    listObjectsRequest.set_max_keys(500);
    ListObjectsResponse listObjectsResponse;
    int ret = _client.list_objects(listObjectsRequest, &listObjectsResponse);

    for(const ObjectSummary& objectSummary :listObjectsResponse.contents()) {
        BackgroundImage* background_image = resp->add_background_images();
        background_image->set_name(StringUtils::replace_all(objectSummary.key, "background-image/", ""));
        background_image->set_url("https://" + STARS_BUCKET + ".bj.bcebos.com/" + objectSummary.key);
    }

    done->Run();
}

void HeliosServiceImpl::emoji(::google::protobuf::RpcController* controller,
       const helios::EmojiReq* req,
       helios::EmojiResp* resp,
       ::google::protobuf::Closure* done)
{
    ListObjectsRequest listObjectsRequest(STARS_BUCKET);
    std::stringstream prefix;
    prefix << "emoji/" << req->key();
    listObjectsRequest.set_prefix(prefix.str().c_str());
    listObjectsRequest.set_max_keys(500);
    ListObjectsResponse listObjectsResponse;
    int ret = _client.list_objects(listObjectsRequest, &listObjectsResponse);

    for(const ObjectSummary& objectSummary :listObjectsResponse.contents()) {
        Emoji* emoji = resp->add_emojis();
        emoji->set_name(StringUtils::replace_all(objectSummary.key, "emoji/", ""));
        emoji->set_url("https://" + STARS_BUCKET + ".bj.bcebos.com/" + objectSummary.key);
    }

    done->Run();
}

}
