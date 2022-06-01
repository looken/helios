#include <iostream>
#include <sstream>

#include <sofa/pbrpc/pbrpc.h>

#include <helios_service.h>

int main()
{
    sofa::pbrpc::RpcServerOptions options;
    sofa::pbrpc::RpcServer rpc_server(options);

    std::stringstream addr;
    addr << "0.0.0.0:8123";

    if (!rpc_server.Start(addr.str())) {
        return EXIT_FAILURE;
    }

    helios::HeliosServiceImpl* service = new helios::HeliosServiceImpl();
    if (!rpc_server.RegisterService(service)) {
        return EXIT_FAILURE;
    }

    rpc_server.Run();
    rpc_server.Stop();
    return 0;
}
