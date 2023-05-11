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
      char buffer[256];
      int c = sock.receiveBytes(buffer, sizeof(buffer));
      while (c > 0) {
        sock.sendBytes(buffer, c);
        c = sock.receiveBytes(buffer, sizeof(buffer));
      }
    } catch (Poco::Exception& exc) { 
      cerr << "ReverseStringConnection: " << exc.displayText() << endl;
    }
  }
};

int main() {
    TCPServer server(new TCPServerConnectionFactoryImpl<ReverseStringConnection>());
    server.start();

    uint portNo = server.socket().address().port();
    //uint portNo = 28888;
    SocketAddress sa("localhost", portNo);
    cout << "Port no. to be assigned: " << portNo << endl;
    StreamSocket sock(sa);
    cout << "Welcome to POCO TCP server. Enter your string:" << endl;
    while (1) {
      string data;
      cout << "Input by a person" << endl;
      cin >> data;
      reverse(data.begin(), data.end());
      sock.sendBytes(data.data(), (int)data.size());
      char buffer[256] = {0};
      int n = sock.receiveBytes(buffer, sizeof(buffer));
      cout << "Output by server" << endl;
      cout << string(buffer, n) << endl;
    }

    server.stop();
}
