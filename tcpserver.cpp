#include <iostream>
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"


using namespace std;
using namespace Poco;
using namespace Net;

class ReverseStringConnection: public TCPServerConnection {
public:
  ReverseStringConnection(const StreamSocket& s): TCPServerConnection(s) { }

  void run() {
    StreamSocket &sock = socket();
    try {
      char *buffer = new char[256];
      buffer[256] = {0};
      int c = sock.receiveBytes(buffer, sizeof(buffer));
      while (c > 0) {
        string data(buffer);
        reverse(data.begin(), data.end());
        sock.sendBytes(data.c_str(), data.size());
	char *temp_buffer = buffer;
        buffer = new char[256];
        buffer[256] = {0};
	delete [] temp_buffer;
        c = sock.receiveBytes(buffer, sizeof(buffer));
      }
    } catch (Exception& exc) { 
      cerr << "ReverseStringConnection: " << exc.displayText() << endl;
    }
  }
};

int main() {
    int portNo = 28888;
    TCPServer server(new TCPServerConnectionFactoryImpl<ReverseStringConnection>(), portNo);
    server.start();

    test(portNo);
}


void test(uint portNo) {
    SocketAddress sa("localhost", portNo);
    cout << "Port no. to be assigned: " << portNo << endl;
    StreamSocket sock(sa);
    cout << "Welcome to POCO TCP server running on port: " << portNo << ". Enter your string:" << endl;
    while (1) {
      string data;
      cout << "Input by a person" << endl;
      cin >> data;
      sock.sendBytes(data.data(), (int)data.size());
      char buffer[256] = {0};
      int n = sock.receiveBytes(buffer, sizeof(buffer));
      cout << "Output by server" << endl;
      cout << string(buffer, n) << endl;
    }

    server.stop();
}
