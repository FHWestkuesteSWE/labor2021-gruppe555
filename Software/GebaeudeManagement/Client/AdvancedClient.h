#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class AdvancedClient
{

	boost::asio::io_service io_service;
	tcp::socket s;


	AdvancedClient(char server[], char port[]);
	~AdvancedClient();



	void sendRequest(tcp::socket, const char request[]);
	void recvhandler(const boost::system::error_code& error, std::size_t bytes_transferred);

	tcp::socket connect();
	void disconnect();

	


protected:



	static const int max_length = 1024;
	const char answer[max_length];

	char* server, * port;


};

