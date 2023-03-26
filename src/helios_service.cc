#include <helios_service.h>

#include "time.h"

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

void HeliosServiceImpl::timestamp_to_date(::google::protobuf::RpcController* controller,
                                          const helios::TimeStampToDateReq* req,
                                          helios::TimeStampToDateResp* resp,
                                          ::google::protobuf::Closure* done)
{
    uint64_t ts = req->timestamp();
    time_t tick = (time_t)ts;
    struct tm tm;
    char s[100];
    tm = *localtime(&tick);
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);
    resp->set_timestamp(ts);
    resp->set_date(s);
    done->Run();
}

void HeliosServiceImpl::date_to_timestamp(::google::protobuf::RpcController* controller,
                                          const helios::DateToTimeStampReq* req,
                                          helios::DateToTimeStampResp* resp,
                                          ::google::protobuf::Closure* done)
{
    std::string date(req->date());
    struct tm tm;
    strptime(date.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
    resp->set_date(date);
    resp->set_timestamp(mktime(&tm));
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
        std::string name(StringUtils::replace_all(objectSummary.key, "background-image/", ""));
        if (name.empty()) {
            continue;
        }
        BackgroundImage* background_image = resp->add_background_images();
        background_image->set_name(name);
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

void HeliosServiceImpl::zuowen(::google::protobuf::RpcController* controller,
                               const helios::ZuowenReq* req,
                               helios::ZuowenResp* resp,
                               ::google::protobuf::Closure* done)
{
    ListObjectsRequest listObjectsRequest(STARS_BUCKET);
    std::stringstream prefix;
    prefix << "learn/" << req->key();
    listObjectsRequest.set_prefix(prefix.str().c_str());
    listObjectsRequest.set_max_keys(1000);
    ListObjectsResponse listObjectsResponse;
    int ret = _client.list_objects(listObjectsRequest, &listObjectsResponse);

    std::vector<std::pair<std::string, std::string>> zuowens;
    for (auto it : listObjectsResponse.common_prefixes()) {
        std::cout << it << std::endl;
    }
    for(const ObjectSummary& objectSummary :listObjectsResponse.contents()) {
        std::vector<std::string> tmp_arr;
        StringUtils::split(objectSummary.key, "/", &tmp_arr);
        if (tmp_arr.empty()) {
            continue;
        }
        zuowens.push_back(std::make_pair(StringUtils::replace_all(tmp_arr[tmp_arr.size() - 1], ".txt", ""), "https://" + STARS_BUCKET + ".bj.bcebos.com/" + objectSummary.key));
    }

    int cnt = 0;
    while (!zuowens.empty()) {
        int i = rand() % zuowens.size();
        ZuowenInfo* zuowen_info = resp->add_zuowen_infos();
        std::vector<std::string> tmp_arr;
        StringUtils::split(zuowens[i].second, "/", &tmp_arr);
        if (tmp_arr.size() >= 3) {
            zuowen_info->set_grade(tmp_arr[tmp_arr.size() - 3]);
            zuowen_info->set_type(tmp_arr[tmp_arr.size() - 2]);
        }
        zuowen_info->set_name(zuowens[i].first);
        zuowen_info->set_url(zuowens[i].second);
        cnt++;
        zuowens.erase(zuowens.begin() + i);
        if (cnt >= 50) {
            break;
        }
    }

    done->Run();
}

void HeliosServiceImpl::zuowen_type(::google::protobuf::RpcController* controller,
                                    const helios::ZuowenTypeReq* req,
                                    helios::ZuowenTypeResp* resp,
                                    ::google::protobuf::Closure* done)
{
    std::map<std::string, std::set<std::string>> conf;
    conf["小学"] = std::set<std::string>({"一年级", "二年级", "三年级", "四年级", "五年级", "六年级"});
    conf["初中"] = std::set<std::string>({"初一", "初二", "初三"});
    conf["高中"] = std::set<std::string>({"高一", "高二", "高三"});
    auto grades = conf.find(req->level());
    if (grades == conf.end()) {
        resp->set_level(req->level());
        done->Run();
        return;
    }
    for (auto it : grades->second) {
        helios::ZuowenType* zuowen_type = resp->add_zuowen_types();
        zuowen_type->set_grade(it);
        ListObjectsRequest listObjectsRequest(STARS_BUCKET);
        std::string prefix("learn/" + req->level() + "/" + it + "/");
        listObjectsRequest.set_prefix(prefix.c_str());
        listObjectsRequest.set_delimiter("/");
        listObjectsRequest.set_max_keys(1000);
        ListObjectsResponse listObjectsResponse;
        int ret = _client.list_objects(listObjectsRequest, &listObjectsResponse);
        for (auto it : listObjectsResponse.common_prefixes()) {
            std::vector<std::string> tmp_arr;
            StringUtils::split(it, "/", &tmp_arr);
            if (tmp_arr.size() < 2) {
                continue;
            }
            zuowen_type->add_types(tmp_arr[tmp_arr.size() - 2]);
        }
    }
    resp->set_level(req->level());
    done->Run();
}

void HeliosServiceImpl::tools_list(::google::protobuf::RpcController* controller,
                                   const helios::ToolsListReq* req,
                                   helios::ToolsListResp* resp,
                                   ::google::protobuf::Closure* done)
{
    std::vector<std::pair<std::string, std::string>> items{
        {"qrcode", "二维码"}
    };
    for (auto item : items) {
        ToolsItem* it = resp->add_content();
        it->set_id(item.first);
        it->set_name(item.second);
    }
    done->Run();
}

}
