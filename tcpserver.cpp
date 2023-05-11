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
    TCPServer srv(new TCPServerConnectionFactoryImpl<ReverseStringConnection>());
    srv.start();

    SocketAddress sa("localhost", srv.socket().address().port());
    StreamSocket sock(sa);
    while (1) {
      string data;	    
      //string data("hello, world");
      cin >> data;
      sock.sendBytes(data.data(), (int)data.size());
      char buffer[256] = {0};
      int n = sock.receiveBytes(buffer, sizeof(buffer));
      cout << string(buffer, n) << endl;
    }

    srv.stop();
}
