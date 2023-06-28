#include"RPCServer.h"
#include<grpcpp/grpcpp.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using std::string;



grpc::Status ClientNamenodeServiceImpl::GetBlockLocation(grpc::ServerContext *context,
                                                         const ClientNamenode::GetBlockLocationsRequest *request,
                                                         ClientNamenode::GetBlockLocationResponse *response) {
    return grpc::Status();
}

grpc::Status ClientNamenodeServiceImpl::GetServerDefaults(grpc::ServerContext *context,
                                                          const ClientNamenode::GetServerDefaultsRequest *request,
                                                          ClientNamenode::GetServerDefaultsResponse *response) {
    return Service::GetServerDefaults(context, request, response);
}

grpc::Status
ClientNamenodeServiceImpl::Create(grpc::ServerContext *context, const ClientNamenode::CreateRequest *request,
                                  ClientNamenode::CreateResponse *response) {
    INode* node = m_nameSystem->addFile(request);
    if(node!= nullptr){
        FileStatus* status = new FileStatus();
        status->set_owner("lx");
        response->set_allocated_status(status);
    }else{
        response->set_allocated_status(nullptr);
    }
    return Status::OK;
}

grpc::Status
ClientNamenodeServiceImpl::Append(grpc::ServerContext *context, const ClientNamenode::AppendRequest *request,
                                  ClientNamenode::AppendResponse *response) {
    return Service::Append(context, request, response);
}

grpc::Status
ClientNamenodeServiceImpl::Rename(grpc::ServerContext *context, const ClientNamenode::RenameRequest *request,
                                  ClientNamenode::RenameResponse *response) {

    response->set_result(m_nameSystem->rename(request));
    return Status::OK;
}

grpc::Status
ClientNamenodeServiceImpl::Delete(grpc::ServerContext *context, const ClientNamenode::DeleteRequest *request,
                                  ClientNamenode::DeleteResponse *response) {
    response->set_result(m_nameSystem->deleteNode(request));
    return Status::OK;
}

grpc::Status
ClientNamenodeServiceImpl::SetOwner(grpc::ServerContext *context, const ClientNamenode::SetOwnerRequest *request,
                                    ClientNamenode::SetOwnerResponse *response) {
    return Service::SetOwner(context, request, response);
}

grpc::Status ClientNamenodeServiceImpl::SetPermission(grpc::ServerContext *context,
                                                      const ClientNamenode::SetPermissionRequest *request,
                                                      ClientNamenode::SetPermissionResponse *response) {
    return Service::SetPermission(context, request, response);
}

grpc::Status ClientNamenodeServiceImpl::mkdir(grpc::ServerContext *context, const ClientNamenode::mkdirRequest *request,
                                              ClientNamenode::mkdirResponse *response) {
    INode* node = m_nameSystem->addDir(request);
    if(node != nullptr){
        response->set_issuccess(true);
    }else{
        response->set_issuccess(false);
    }
    return Status::OK;
}

grpc::Status
ClientNamenodeServiceImpl::Listing(grpc::ServerContext *context, const ClientNamenode::GetListingRequest *request,
                                   ClientNamenode::GetListingResponse *response) {
    vector<INode*> children = m_nameSystem->list(request);
    if (!children.empty()){
        auto* listing = new DirestoryListing();
        for (auto & i : children) {
            FileStatus* status = listing->add_partiallisting();
            status->set_path(i->getFullPathName());
        }
        response->set_allocated_dirlist(listing);
//        long size = response->ByteSizeLong();
//        void* p = malloc(size);
//        response->SerializeToArray(p,size);
    }else{
        response->set_allocated_dirlist(nullptr);
    }
    return Status::OK;
}

grpc::Status
ClientNamenodeServiceImpl::RenewLease(grpc::ServerContext *context, const ClientNamenode::RenewLeaseRequest *request,
                                      ClientNamenode::RenewLeaseResponse *response) {
    return grpc::Status();
}

ClientNamenodeServiceImpl::ClientNamenodeServiceImpl(namesystem::NameSystem *nameSystem):m_nameSystem(nameSystem) {

}