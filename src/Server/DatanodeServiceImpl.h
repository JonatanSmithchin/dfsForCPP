#ifndef DATANODESERVICE_H
#define DATANODESERVICE_H
#include<iostream>
#include<string>
#include<grpcpp/grpcpp.h>
#include<string>
#include"../../proto/DatanodeNamenode.grpc.pb.h"
#include"../../proto/dfs.pb.h"
#include"../Datanode/DatanodeManager.h"

class DatanodeServiceImpl final :public DatanodeNamenode::DatanodeService::Service{
private:
    datanode::DatanodeManager* m_datanodeManager;
public:
    DatanodeServiceImpl(datanode::DatanodeManager* manager);

    grpc::Status
    registerDatanode(::grpc::ServerContext *context, const ::DatanodeNamenode::RegisterDatanodeRequest *request,
                     ::DatanodeNamenode::RegisterDatanodeResponse *response) override;

    grpc::Status sendHeartBeat(::grpc::ServerContext *context, const ::DatanodeNamenode::HeartBeatRequest *request,
                               ::DatanodeNamenode::HeartBeatResponse *response) override;

    grpc::Status blockReport(::grpc::ServerContext *context, const ::DatanodeNamenode::blockReportRequest *request,
                             ::DatanodeNamenode::blockReportResponse *response) override;

    grpc::Status cacheReport(::grpc::ServerContext *context, const ::DatanodeNamenode::cacheReportRequest *request,
                             ::DatanodeNamenode::cacheReportResponse *response) override;

    grpc::Status blockReceivedAndDeleted(::grpc::ServerContext *context,
                                         const ::DatanodeNamenode::BlockReceivedAndDeletedRequest *request,
                                         ::DatanodeNamenode::BlockReceivedAndDeletedResponse *response) override;

    grpc::Status errorReport(::grpc::ServerContext *context, const ::DatanodeNamenode::ErrorReportRequest *request,
                             ::DatanodeNamenode::ErrorReportResponse *response) override;

    grpc::Status
    reportBadBlock(::grpc::ServerContext *context, const ::DatanodeNamenode::ReportBadBlockRequest *request,
                   ::DatanodeNamenode::ReportBadBlockResponse *response) override;
};

#endif