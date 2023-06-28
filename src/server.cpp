#include<iostream>
#include<string>

#include<grpcpp/grpcpp.h>

#include"../proto/helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

class GreeterServiceImpl final :public Greeter::Service {
	Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) {
		std::string prefix("Hello! ");
		reply->set_message(prefix + request->name());
		return Status::OK;
	}
};

void RunServer() {
	std::string server_address("0.0.0.0:8500");
	GreeterServiceImpl service;

	ServerBuilder builder;

	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

	builder.RegisterService(&service);

	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "server listening on " << server_address << std::endl;
	server->Wait();
}

int main() {
	RunServer();
	return 0;
}