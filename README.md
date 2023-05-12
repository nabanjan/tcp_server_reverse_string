
Please select an ubuntu linux machine with latest OS



Please install all pre-requisites

g++ - gnu cpp compiler
# sudo apt-get install g++

libssl-dev - ssl dev library -  pre-requisite for poco dev library
# sudo apt-get install libssl-dev

poco dev library
# sudo apt-get install libpoco-dev



Allow port 28888 to receive connection - open the port 
# sudo ufw allow 28888

Make sure everytime one runs the server, nothing is running in port 28888
# sudo fuser 28888/tcp

Above outputs process ids if any process is holding port 28888;
If process(es) is/are holding the port, kill those process(es) using below command
# kill -9 <process id 1> <process id 2> ....


Now build the tcp server using below script
# ./build.sh


Now, run the tcp server to reverse a string in background 
# ./tcpserver &


Use telnet to send sequence of characters - note that the Nagle's algorithm is disabled for a chatty protocol like telnet; 
small burst of payload will be sent - this results in chunks of a long string typed by a human user in a telnet session is sent;
this results in server interpreting that multiple strings are sent and so sends back reversed multiple strings 
# telnet localhost 28888

Enter strings in the telnet session - the reverse of the string will be echoed back immediately.


After the session is over, to shutdown the server, do below:
# fg
Above will bring the tcpserver to foreground
Now, do CTRL-C - this will shutdown the server
