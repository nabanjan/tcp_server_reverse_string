#!/bin/bash
clear
g++ -std=c++14 ./tcpserver.cpp -o tcpserver -lPocoFoundation -lPocoNet -lPocoUtil 
