#include"RPCServer.h"
#include<grpcpp/grpcpp.h>
#include"ClientServiceImpl.h"
#include"DatanodeServiceImpl.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using std::string;

void RPCServer::RunServer() {
    string server_address("[::]:4491");

    ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    builder.RegisterService(m_client_service);
    builder.RegisterService(m_datanode_service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "server listeningn on " << server_address << std::endl;
    std::cout <<"root:";
    INodeDir* root= m_nameSystem->getRoot();
    std::cout<<root->getName();
    server->Wait();
}

RPCServer::RPCServer(namesystem::NameSystem* nameSystem,ClientNamenodeServiceImpl* ClientNamenodeService,DatanodeServiceImpl* DatanodeService):
        m_nameSystem(nameSystem),m_client_service(ClientNamenodeService),m_datanode_service(DatanodeService){
}

int main() {
    //启动namenode的Server
    std::cout<<"start server"<<std::endl;
    std::cout<<"Init namesystem...";
    //初始化
    INodeDir root;
    //加载NameSystem
    auto nameSystem = namesystem::NameSystem(&root);
    auto datanodeManager = datanode::DatanodeManager();
    //创建ClientService
    ClientNamenodeServiceImpl ClientNamenodeService(&nameSystem);
    DatanodeServiceImpl DatanodeService(&datanodeManager);
    std::cout<<"run server"<<std::endl;
    //启动服务
    RPCServer server = RPCServer(&nameSystem,&ClientNamenodeService,&DatanodeService);
    server.RunServer();
}
