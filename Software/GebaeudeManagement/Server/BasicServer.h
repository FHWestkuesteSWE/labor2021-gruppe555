#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>
#include "Raum.h"

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

class BasicServer
{
public:
	void start(int port);
	BasicServer();
	~BasicServer();
	const static int max_length=1024;

	bool read_config(char path[]);

private:
	void session(socket_ptr sock);
	virtual void processRequest(char request[], char answer[]);

	std::vector<Raum> vec_raum;
};

