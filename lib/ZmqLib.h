#ifndef ZMQ_LIB_H
#define ZMQ_LIB_H

#include <string>
#include <zmq.hpp>

class ZmqLib
{
public:
	ZmqLib(int threadNum, zmq::socket_type socketType) : Context(threadNum), Socket(Context, socketType) {}
	void ConnectSocket(std::string socketAddress);
	void SendMsg(std::string inputLine);
	std::string GetReplyMsg();

private:
	zmq::context_t Context;
	zmq::socket_t Socket;
};
#endif