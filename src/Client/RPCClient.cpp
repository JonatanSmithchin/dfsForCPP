//
// Created by 刘晓 on 2023/6/14.
//
#include<iostream>
#include<string>
#include<grpcpp/grpcpp.h>
#include "../../proto/ClientNamenode.grpc.pb.h"
#include "../../proto/dfs.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using ClientNamenode::AppendRequest;
using ClientNamenode::AppendResponse;
using ClientNamenode::ClientService;
using namespace ClientNamenode;

class Client {
public:
    Client(std::shared_ptr<Channel> channel)
            : stub_(ClientService::NewStub(channel)){}

    std::string create(const std::string src){
        CreateRequest request;
        request.set_src(src);

        CreateResponse response;
        ClientContext context;

        Status status = stub_->Create(&context,request,&response);

        if (status.ok()){
            return response.status().owner();
        }else{
            std::cout << status.error_code() << ":" << status.error_message() << std::endl;
            return "RPC failed";
        }
    }

    std::string mkdir(const std::string src){
        mkdirRequest request;
        request.set_src(src);

        mkdirResponse response;

        ClientContext context;

        Status status = stub_->mkdir(&context,request,&response);

        if (status.ok()){
            if (response.issuccess()){
                std::cout<<"mkdir: "<<src<< std::endl;
                return "success";
            }
        }else{
            std::cout << status.error_code() << ":" << status.error_message() << std::endl;
            return "RPC failed";
        }
        return "";
    }

    std::string List(const std::string& dir){
        GetListingRequest request;
        request.set_src(dir);

        GetListingResponse response;

        ClientContext context;

        Status status = stub_->Listing(&context,request,&response);

        if(status.ok()){
            for (int i = 0; i < response.dirlist().partiallisting_size(); ++i) {
                std::cout<<response.dirlist().partiallisting(i).path()<<std::endl;
            }
            return "finished";
        }else{
            std::cout << status.error_code() << ":" << status.error_message() << std::endl;
            return "RPC failed";
        }
    }

    std::string Delete(const std::string& src){
        DeleteRequest request;
        request.set_src(src);

        DeleteResponse response;

        ClientContext context;

        Status status = stub_->Delete(&context,request,&response);

        if(status.ok()){
            if(response.result()){
                return "delete";
            }else{
                return "failed";
            }
        }else{
            std::cout << status.error_code() << ":" << status.error_message() << std::endl;
            return "RPC failed";
        }
    }

    std::string Append(const std::string& user) {
        AppendRequest request;
        request.set_clientname(user);

        AppendResponse reply;

        ClientContext context;

        Status status = stub_->Append(&context, request, &reply);

        if (status.ok()) {
            return reply.GetTypeName();
        }
        else {
            std::cout << status.error_code() << ":" << status.error_message() << std::endl;
            return "RPC failed";
        }
    }
private:
    std::unique_ptr<ClientService::Stub> stub_;
};

int main() {
    Client client(grpc::CreateChannel(
            "localhost:4491", grpc::InsecureChannelCredentials()
    ));

    int opt;
    while(1){
        std::cin>>opt;
        std::string src;
        std::string reply;
        switch(opt){
            case 0:
                std::cin>>src;
                reply = client.create(src);
                break;
            case 1:
                std::cin>>src;
                reply = client.mkdir(src);
                break;
            case 2:
                std::cin>>src;
                reply = client.List(src);
                break;
            case 3:
                std::cin>>src;
                reply = client.Delete(src);
                break;
            default:
                break;
        }
        std::cout << "greeter received: " << reply << std::endl;
    }

    return 0;
}