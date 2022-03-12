#include <zmq.hpp>
#include <string>
#include <iostream>
#include <fstream>

using namespace zmq;
using namespace std;

int main()
{
    // Open input file from txt.
    ifstream inputFile;
    inputFile.open("input.txt");

    // Create and open output file.
    ofstream outputFile;
    outputFile.open("output.txt");

    // Specifies the size of the 0MQ thread pool to handle operations.
    // If your application is using only the inproc transport for 
    // messaging you may set this to zero, otherwise set it to at least one.
    const int ZMQ_IO_THREAD_NUM = 1;

    // Transport and address data of socket connection.
    const string ZMQ_CONNECTION_TRANSPORT_TCP = "tcp://";
    const string ZMQ_CONNECTION_ADDRESS = "localhost:5555";

    // Prepare our context and socket
    context_t context(ZMQ_IO_THREAD_NUM);

    // Create Socket and Connect
    // A socket of type ZMQ_REQ is used by a client to send requests to 
    // and receive replies from a service.
    socket_t socket(context, socket_type::req);
    socket.connect(ZMQ_CONNECTION_TRANSPORT_TCP + ZMQ_CONNECTION_ADDRESS);
    
    // Lines of input files.
    string inputLine;

    while ( getline(inputFile, inputLine) )
    {
        // Set line size variable according to line length.
        int lineSize = inputLine.size();

        // Set and send request to server.
        message_t request(lineSize);
        memcpy(request.data(), inputLine.c_str(), lineSize);
        socket.send(request, send_flags::none);

        // Get the reply from server.
        message_t reply;
        socket.recv(reply, recv_flags::none);

        // Convert reply message to string.
        string replyStr = string(static_cast<char*>(reply.data()), reply.size());

        // Write reply message to file.
        outputFile << replyStr << "\n";
    }

    // Close output file after writing reply results.
    outputFile.close();
    
    return 0;
}
