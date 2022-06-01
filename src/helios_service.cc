#include <helios_service.h>

namespace helios {

void HeliosServiceImpl::emoji(::google::protobuf::RpcController* controller,
       const helios::EmojiReq* req,
       helios::EmojiResp* resp,
       ::google::protobuf::Closure* done)
{
    done->Run();
}

}
