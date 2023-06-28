#include"RPCServer.h"
#include<grpcpp/grpcpp.h>
#include"DatanodeServiceImpl.h"
#include<vector>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using std::string;

Status DatanodeServiceImpl::registerDatanode(::grpc::ServerContext *context,
                                             const ::DatanodeNamenode::RegisterDatanodeRequest *request,
                                             ::DatanodeNamenode::RegisterDatanodeResponse *response) {
    DatanodeDescriptor d;
    d.setId(request->registration().id().datanodeuuid());
    m_datanodeManager->addDatanode(&d);
    string host = "datanode1";
    auto* id = new DatanodeID;
    id->set_hostname(host);
    auto* r = new DatanodeNamenode::DatanodeRegister;
    r->set_allocated_id(id);
    response->set_allocated_registration(r);
    return Status::OK;
}

Status
DatanodeServiceImpl::sendHeartBeat(::grpc::ServerContext *context, const ::DatanodeNamenode::HeartBeatRequest *request,
                                   ::DatanodeNamenode::HeartBeatResponse *response) {

    vector<DatanodeNamenode::DatanodeCommand> cmds = m_datanodeManager->handleHeartBeat();
    for (auto& i:cmds) {
         DatanodeNamenode::DatanodeCommand* cmd = response->add_cmds();
         cmd->CopyFrom(i);
    }

    return Status::OK;
}

Status
DatanodeServiceImpl::blockReport(::grpc::ServerContext *context, const ::DatanodeNamenode::blockReportRequest *request,
                                 ::DatanodeNamenode::blockReportResponse *response) {
    return Service::blockReport(context, request, response);
}

Status
DatanodeServiceImpl::cacheReport(::grpc::ServerContext *context, const ::DatanodeNamenode::cacheReportRequest *request,
                                 ::DatanodeNamenode::cacheReportResponse *response) {
    return Service::cacheReport(context, request, response);
}

Status DatanodeServiceImpl::blockReceivedAndDeleted(::grpc::ServerContext *context,
                                                    const ::DatanodeNamenode::BlockReceivedAndDeletedRequest *request,
                                                    ::DatanodeNamenode::BlockReceivedAndDeletedResponse *response) {
    return Service::blockReceivedAndDeleted(context, request, response);
}

Status
DatanodeServiceImpl::errorReport(::grpc::ServerContext *context, const ::DatanodeNamenode::ErrorReportRequest *request,
                                 ::DatanodeNamenode::ErrorReportResponse *response) {
    return Service::errorReport(context, request, response);
}

Status DatanodeServiceImpl::reportBadBlock(::grpc::ServerContext *context,
                                           const ::DatanodeNamenode::ReportBadBlockRequest *request,
                                           ::DatanodeNamenode::ReportBadBlockResponse *response) {
    return Service::reportBadBlock(context, request, response);
}

DatanodeServiceImpl::DatanodeServiceImpl(datanode::DatanodeManager* manager):m_datanodeManager(manager) {

}