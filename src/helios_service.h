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
    { }

    ~HeliosServiceImpl()
    { }

    void emoji(::google::protobuf::RpcController* controller,
               const helios::EmojiReq* req,
	       helios::EmojiResp* resp,
	       ::google::protobuf::Closure* done);

private:
    int listBuckets (Client& client);

private:
    const std::string ACCESS_KEY_ID = "136da69842234cbdb8b91ed749e3cdee";
    std::string SECRET_ACCESS_KEY = "3dbb8f6af0624679bb7608dac7bc97d3";
};

}

#endif
