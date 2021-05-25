#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <string>
#include <boost/asio/error.hpp>



using boost::asio::steady_timer;
using boost::asio::ip::tcp;

class AdvancedClient
{
public:

    AdvancedClient(boost::asio::io_context& io_context)
        : stopped_(false),
        socket_(io_context),
        deadline_(io_context),
        heartbeat_timer_(io_context)
    {
    }

	
    void start(tcp::resolver::results_type endpoints);
    void stop();


private:

    void start_connect(tcp::resolver::results_type::iterator endpoint_iter);
    void handle_connect(const boost::system::error_code& ec, tcp::resolver::results_type::iterator endpoint_iter);

    void start_read();
    void handle_read(const boost::system::error_code& ec, std::size_t n);
    
public:
    void start_write(std::string req);

private:
    void handle_write(const boost::system::error_code & ec);

       
    void check_deadline();

private:
    bool stopped_;
    tcp::resolver::results_type endpoints_;
    tcp::socket socket_;
    std::string input_buffer_;
    steady_timer deadline_;
    steady_timer heartbeat_timer_;

};

