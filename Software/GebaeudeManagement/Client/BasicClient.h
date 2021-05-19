#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class BasicClient
{
public:


	BasicClient(char server[], char port[]);
	~BasicClient();
	void sendRequest(const char request[], char answer[]);



protected:
	
	static const int max_length=1024;
	
	char *server, *port;

};

