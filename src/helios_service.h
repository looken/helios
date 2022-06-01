#ifndef helios_service_h
#define helios_service_h

#include <helios.pb.h>

#include <sofa/pbrpc/pbrpc.h>

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

};

}

#endif
