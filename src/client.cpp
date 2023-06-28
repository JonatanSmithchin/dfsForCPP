#include<iostream>
#include<string>
#include<grpcpp/grpcpp.h>
#include "../proto/helloworld.grpc.pb.h"
#include "../proto/ClientNamenode.grpc.pb.h"
#include "../proto/dfs.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

class GreeterClient {
public:
	GreeterClient(std::shared_ptr<Channel> channel)
		: stub_(Greeter::NewStub(channel)){}
	std::string SayHello(const std::string& user) {
		HelloRequest request;
		request.set_name(user);

		HelloReply reply;

		ClientContext context;

		Status status = stub_->SayHello(&context, request, &reply);

		if (status.ok()) {
			return reply.message();
		}
		else {
			std::cout << status.error_code() << ":" << status.error_message() << std::endl;
			return "RPC failed";
		}
	}
private:
	std::unique_ptr<Greeter::Stub> stub_;
};

int main() {
	GreeterClient client(grpc::CreateChannel(
		"localhost:8500", grpc::InsecureChannelCredentials()
	));

	std::string user("world");
	std::string reply = client.SayHello(user);
	std::cout << "greeter received: " << reply << std::endl;

	return 0;
}