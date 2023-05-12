#include <iostream>

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"


using namespace std;
using namespace Poco;
using namespace Poco::Net;



class ReverseStringConnection: public TCPServerConnection {
public:
  ReverseStringConnection(const StreamSocket& s): TCPServerConnection(s) { }

  void run() {
    StreamSocket &sock = socket();
    sock.setReceiveBufferSize(255);
    try {
      char *buffer = new char[256];
      buffer[256] = {0};
      int c = sock.receiveBytes(buffer, sizeof(buffer));
      time_t start_time;
      time_t end_time;
      while (c > 0) {
        string data(buffer);
        reverse(data.begin(), data.end());
        sock.sendBytes(data.c_str(), data.size());
	char *temp_buffer = buffer;
        buffer = new char[256];
        buffer[256] = {0};
	delete [] temp_buffer;
	start_time = time(NULL);
        c = sock.receiveBytes(buffer, sizeof(buffer));
	end_time = time(NULL);
      }
    } catch (Exception& e) { 
      cerr << "ReverseStringConnection: " << e.displayText() << endl;
    }
  }
};


/* TEST CODE STARTS
void test(uint portNo) {
    SocketAddress sa("localhost", portNo);
    cout << "Port no. to be assigned: " << portNo << endl;
    StreamSocket sock(sa);
    while (true) {
      string data;
      cin >> data;
      sock.sendBytes(data.data(), (int)data.size());
      char buffer[256] = {0};
      int n = sock.receiveBytes(buffer, sizeof(buffer));
      cout << string(buffer, n) << endl;
    }
}
*/ //TEST CODE STARTS

int main() {
    int portNo = 28888;
    TCPServer localserver(new TCPServerConnectionFactoryImpl<ReverseStringConnection>(), portNo);
    cout << "Welcome to POCO TCP server running on port: " << portNo << ". Enter your string:" << endl;
    localserver.start();
    //test(portNo);
    while (true);
    localserver.stop();
}
