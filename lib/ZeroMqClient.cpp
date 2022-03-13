#include "ZeroMqClient.h"
#include "ZmqLib.h"
#include <fstream>

int main()
{
    // Specifies the size of the 0MQ thread pool to handle operations.
    // If your application is using only the inproc transport for 
    // messaging you may set this to zero, otherwise set it to at least one.
    int ZMQ_LOCAL_TCP_THREAD_NUM = 1;

    // Specifies the local TCP connection address with server.
    std::string ZMQ_LOCAL_TCP_ADDRESS = "tcp://localhost:5555";

    // İnput and output file paths.
    const std::string INPUT_FILE_PATH = "input.txt";
    const std::string OUTPUT_FILE_PATH = "output.txt";

    // Open input file.
    std::ifstream inputFile(INPUT_FILE_PATH);

    // Open output file.
    std::ofstream outputFile(OUTPUT_FILE_PATH);

    ZmqLib zmqLocalTcpClient(ZMQ_LOCAL_TCP_THREAD_NUM, zmq::socket_type::req);
    zmqLocalTcpClient.ConnectSocket(ZMQ_LOCAL_TCP_ADDRESS);

    // Lines of input files.
    std::string inputLine;

    while (getline(inputFile, inputLine))
    {
        zmqLocalTcpClient.SendMsg(inputLine);

        std::string replyMsg = zmqLocalTcpClient.GetReplyMsg();

        outputFile << replyMsg << "\n";
    }

    inputFile.close();
    outputFile.close();
    
    return 0;
}
