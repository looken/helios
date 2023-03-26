#ifndef helios_service_h
#define helios_service_h

#include <bcesdk/bos/client.h>

#include <helios.pb.h>
#include <sofa/pbrpc/pbrpc.h>

using namespace bcesdk_ns;

namespace helios {

class HeliosServiceImpl : public HeliosService
{
public:
    HeliosServiceImpl()
        : _client(ACCESS_KEY_ID, SECRET_ACCESS_KEY)
    {
        _logfp = fopen("log/sdk.log", "w");
        sdk_set_log_stream(_logfp);
        sdk_set_log_level(SDK_LOG_DEBUG);
    }

    ~HeliosServiceImpl()
    {
        fclose(_logfp);
        _logfp = nullptr;
    }

    void base64_encode(::google::protobuf::RpcController* controller,
                       const helios::Base64EncodeReq* req,
                       helios::Base64EncodeResp* resp,
                       ::google::protobuf::Closure* done);

    void base64_decode(::google::protobuf::RpcController* controller,
                       const helios::Base64DecodeReq* req,
                       helios::Base64DecodeResp* resp,
                       ::google::protobuf::Closure* done);

    void md5_encode(::google::protobuf::RpcController* controller,
                    const helios::Md5EncodeReq* req,
                    helios::Md5EncodeResp* resp,
                    ::google::protobuf::Closure* done);

    void timestamp_to_date(::google::protobuf::RpcController* controller,
                           const helios::TimeStampToDateReq* req,
                           helios::TimeStampToDateResp* resp,
                           ::google::protobuf::Closure* done);

    void date_to_timestamp(::google::protobuf::RpcController* controller,
                           const helios::DateToTimeStampReq* req,
                           helios::DateToTimeStampResp* resp,
                           ::google::protobuf::Closure* done);

    void emoji(::google::protobuf::RpcController* controller,
               const helios::EmojiReq* req,
               helios::EmojiResp* resp,
               ::google::protobuf::Closure* done);

    void background_image(::google::protobuf::RpcController* controller,
                          const helios::BackgroundImageReq* req,
                          helios::BackgroundImageResp* resp,
                          ::google::protobuf::Closure* done);

    void zuowen(::google::protobuf::RpcController* controller,
                const helios::ZuowenReq* req,
                helios::ZuowenResp* resp,
                ::google::protobuf::Closure* done);

    void zuowen_type(::google::protobuf::RpcController* controller,
                     const helios::ZuowenTypeReq* req,
                     helios::ZuowenTypeResp* resp,
                     ::google::protobuf::Closure* done);

    void tools_list(::google::protobuf::RpcController* controller,
                    const helios::ToolsListReq* req,
                    helios::ToolsListResp* resp,
                    ::google::protobuf::Closure* done);

private:
    int listBuckets (Client& client);

private:
    const std::string ACCESS_KEY_ID = "136da69842234cbdb8b91ed749e3cdee";
    const std::string SECRET_ACCESS_KEY = "3dbb8f6af0624679bb7608dac7bc97d3";

    const std::string STARS_BUCKET = "looken-stars";

    FILE* _logfp;
    baidu::bos::cppsdk::Client _client;
};

}

#endif
