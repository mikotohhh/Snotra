#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <snotra.grpc.pb.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using stringprocessor::PromptRequest;
using stringprocessor::PromptReply;
using stringprocessor::StringProcessor;

class StringProcessorClient {
 public:
  StringProcessorClient(std::shared_ptr<Channel> channel)
      : stub_(StringProcessor::NewStub(channel)) {}

  std::string Prompt(const std::string& user_input) {
    PromptRequest request;
    request.set_input(user_input);

    PromptReply reply;

    ClientContext context;

    Status status = stub_->Response(&context, request, &reply);

    if (status.ok()) {
      return reply.output();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<StringProcessor::Stub> stub_;
};

int main(int argc, char** argv) {
  StringProcessorClient client(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  std::string user_input("your string here");
  std::string reply = client.Prompt(user_input);
  std::cout << "Server processed string: " << reply << std::endl;

  return 0;
}
