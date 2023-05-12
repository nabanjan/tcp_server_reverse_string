#!/bin/bash
clear
#sudo apt-get install g++
#sudo apt-get install libssl-dev
#sudo apt-get install libpoco-dev
#sudo ufw allow 28888
#sudo fuser 28888/tcp
g++ -std=c++14 ./tcpserver.cpp -o tcpserver -lPocoFoundation -lPocoNet -lPocoUtil 
