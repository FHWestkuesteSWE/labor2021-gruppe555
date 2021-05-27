#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <list>
#include <ctime>
#include <mutex>
#include <condition_variable>

#include "Raum.h"
#include "StreamBuffer.h"

class BasicServer
{
public:
	void update();

	BasicServer(int port);
	~BasicServer();
	const static int max_length=1024;

	bool read_config(char path[]);
	bool end_flag = 0;

#ifdef UNITTEST
	void testrequest(char* request, char* answer);
#endif

private:
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::tcp::acceptor* a;
	std::list<boost::asio::ip::tcp::socket*> sockets;
	std::list<std::thread*> threads;
	std::list<bool> thread_callbacks;

	void session();
	void clear_up_lists();
	static void asio_callback(const boost::system::error_code& ec);
	void processRequest(char* request, char* answer, boost::asio::ip::tcp::socket* sock);
	bool send_log_file(const char log_file_path[], boost::asio::ip::tcp::socket* sock);

	std::vector<Raum> vec_raum;
};

