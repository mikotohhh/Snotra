#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <snotra.grpc.pb.h>


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using stringprocessor::PromptRequest;
using stringprocessor::PromptReply;
using stringprocessor::StringProcessor;

class StringProcessorServiceImpl final : public StringProcessor::Service {
  Status Response(ServerContext* context, const PromptRequest* request,
                  PromptReply* reply) override {
    std::string input = request->input();
    std::string output = std::string("Chatbot Reponse");
    reply->set_output(output);
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  StringProcessorServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
