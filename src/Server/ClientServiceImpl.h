#pragma once
#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H
#include<iostream>
#include<string>
#include<grpcpp/grpcpp.h>
#include<string>
#include"../../proto/ClientNamenode.grpc.pb.h"
#include"../../proto/dfs.pb.h"
#include"../NameSystem/NameSystem.h"

class ClientNamenodeServiceImpl final :public ClientNamenode::ClientService::Service {
private:
    namesystem::NameSystem* m_nameSystem;
public:
    ClientNamenodeServiceImpl(namesystem::NameSystem* nameSystem);
    grpc::Status GetBlockLocation(grpc::ServerContext* context, const ClientNamenode::GetBlockLocationsRequest* request, ClientNamenode::GetBlockLocationResponse* response) override;

    grpc::Status GetServerDefaults(grpc::ServerContext* context, const ClientNamenode::GetServerDefaultsRequest* request, ClientNamenode::GetServerDefaultsResponse* response) override ;

    grpc::Status Create(grpc::ServerContext* context, const ClientNamenode::CreateRequest* request, ClientNamenode::CreateResponse* response) ;

    grpc::Status Append(grpc::ServerContext* context, const ClientNamenode::AppendRequest* request, ClientNamenode::AppendResponse* response) ;

    grpc::Status Rename(grpc::ServerContext* context, const ClientNamenode::RenameRequest* request, ClientNamenode::RenameResponse* response) ;

    grpc::Status Delete(grpc::ServerContext* context, const ClientNamenode::DeleteRequest* request, ClientNamenode::DeleteResponse* response) ;

    grpc::Status SetOwner(grpc::ServerContext* context, const ClientNamenode::SetOwnerRequest* request, ClientNamenode::SetOwnerResponse* response) ;

    grpc::Status SetPermission(grpc::ServerContext* context, const ClientNamenode::SetPermissionRequest* request, ClientNamenode::SetPermissionResponse* response) ;

    grpc::Status mkdir(grpc::ServerContext* context, const ClientNamenode::mkdirRequest* request, ClientNamenode::mkdirResponse* response);

    grpc::Status Listing(grpc::ServerContext* context, const ClientNamenode::GetListingRequest* request, ClientNamenode::GetListingResponse* response) ;

    grpc::Status RenewLease(grpc::ServerContext* context, const ClientNamenode::RenewLeaseRequest* request, ClientNamenode::RenewLeaseResponse* response);
};
#endif