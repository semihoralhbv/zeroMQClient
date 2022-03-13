#include "ZmqLib.h"

void ZmqLib::ConnectSocket(std::string socketAddress)
{
    // Create Socket and Connect
    // A socket of type ZMQ_REQ is used by a client to send requests to 
    // and receive replies from a service.
    Socket.connect(socketAddress);
}

void ZmqLib::SendMsg(std::string inputLine)
{
    // Set line size variable according to line length.
    int lineSize = inputLine.size();

    // Set and send request to server.
    zmq::message_t request(lineSize);
    memcpy(request.data(), inputLine.c_str(), lineSize);
    Socket.send(request, zmq::send_flags::none);
}

std::string ZmqLib::GetReplyMsg()
{
    // Get the reply from server.
    zmq::message_t reply;
    Socket.recv(reply, zmq::recv_flags::none);

    // Convert reply message to string.
    std::string replyStr = std::string(static_cast<char*>(reply.data()), reply.size());

    return replyStr;
}