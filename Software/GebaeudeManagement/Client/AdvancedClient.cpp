#include "AdvancedClient.h"
#include "boost/bind.hpp"



AdvancedClient::AdvancedClient(char _server[], char _port[]) {
	server = _server;
	port = _port;
}

void AdvancedClient::sendRequest(tcp::socket s, const char request[]) {

	size_t request_length = strlen(request) + 1;
	boost::asio::write(s, boost::asio::buffer(request, request_length));

}

AdvancedClient::~AdvancedClient() {
	disconnect();
}


void AdvancedClient::recvhandler(const boost::system::error_code& error, std::size_t bytes_transferred) {



}

tcp::socket AdvancedClient::connect() {

	tcp::resolver resolver(AdvancedClient::io_service);
	tcp::resolver::query query(tcp::v4(), server, port);
	tcp::resolver::iterator iterator = resolver.resolve(query);

	
	tcp::socket s(io_service);
	boost::asio::connect(s, iterator);


	boost::asio::async_read(s,boost::asio::buffer(answer, max_length), 
		boost::bind(recvhandler, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
	
	


	return s;
}


void AdvancedClient::disconnect() {

	s.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	s.close();

}