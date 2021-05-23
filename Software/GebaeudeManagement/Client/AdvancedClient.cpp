#include "AdvancedClient.h"

//
// async_tcp_client.cpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

/*
    2nd Author Dix Goerlich
    Derivative of "async_tcp_client.cpp" by Christopher M. Kohlhoff
    modified for a newer version of "boost" and matched to my usecase

*/





void AdvancedClient::start(tcp::resolver::results_type endpoints)
{
    // Start the connect actor.
    endpoints_ = endpoints;
    start_connect(endpoints_.begin());

    // Start the deadline actor. You will note that we're not setting any
    // particular deadline here. Instead, the connect and input actors will
    // update the deadline prior to each asynchronous operation.
    deadline_.async_wait(boost::bind(&AdvancedClient::check_deadline, this));
}

// This function terminates all the actors to shut down the connection. It
// may be called by the user of the client class, or by the class itself in
// response to graceful termination or an unrecoverable error.
void AdvancedClient::stop()
{
    stopped_ = true;
    boost::system::error_code ignored_ec;
    socket_.close(ignored_ec);
    deadline_.cancel();
    heartbeat_timer_.cancel();
}

void AdvancedClient::start_connect(tcp::resolver::results_type::iterator endpoint_iter)
{
    if (endpoint_iter != endpoints_.end())
    {
        std::cout << "Trying " << endpoint_iter->endpoint() << "...\n";

        // Set a deadline for the connect operation.
        deadline_.expires_after(boost::asio::chrono::seconds(60));

        // Start the asynchronous connect operation.
        socket_.async_connect(endpoint_iter->endpoint(),
            boost::bind(&AdvancedClient::handle_connect, this,
                boost::placeholders::_1, endpoint_iter));
    }
    else
    {
        // There are no more endpoints to try. Shut down the client.
        stop();
    }
}

void AdvancedClient::handle_connect(const boost::system::error_code& ec,
    tcp::resolver::results_type::iterator endpoint_iter)
{
    if (stopped_)
        return;

    // The async_connect() function automatically opens the socket at the start
    // of the asynchronous operation. If the socket is closed at this time then
    // the timeout handler must have run first.
    if (!socket_.is_open())
    {
        std::cout << "Connect timed out\n";

        // Try the next available endpoint.
        start_connect(++endpoint_iter);
    }

    // Check if the connect operation failed before the deadline expired.
    else if (ec)
    {
        std::cout << "Connect error: " << ec.message() << "\n";

        // We need to close the socket used in the previous connection attempt
        // before starting a new one.
        socket_.close();

        // Try the next available endpoint.
        start_connect(++endpoint_iter);
    }

    // Otherwise we have successfully established a connection.
    else
    {
        std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";

        // Start the input actor.
        start_read();

        // Start the heartbeat actor.
        //start_write();
    }
}

void AdvancedClient::start_read()
{
    // Set a deadline for the read operation.
    deadline_.expires_after(boost::asio::chrono::hours(6));

    // Start an asynchronous operation to read a newline-delimited message.
    boost::asio::async_read_until(socket_,
        boost::asio::dynamic_buffer(input_buffer_), '\n',
        boost::bind(&AdvancedClient::handle_read, this,
            boost::placeholders::_1, boost::placeholders::_2));
}

void AdvancedClient::handle_read(const boost::system::error_code& ec, std::size_t n)
{
    if (stopped_)
        return;

    if (!ec)
    {
        // Extract the newline-delimited message from the buffer.
        std::string line(input_buffer_.substr(0, n - 1));
        input_buffer_.erase(0, n);

        // Empty messages are heartbeats and so ignored.
        if (!line.empty())
        {
            std::cout << "Received: " << line << "\n";
        }

        start_read();
    }
    else
    {
        std::cout << "Error on receive: " << ec.message() << "\n";

        stop();
    }
}

void AdvancedClient::start_write(const char req[])
{
    if (stopped_)
        return;

    // Start an asynchronous operation to send a heartbeat message.
    boost::asio::async_write(socket_, boost::asio::buffer(req, 1024),
        boost::bind(&AdvancedClient::handle_write, this, boost::placeholders::_1));
}

void AdvancedClient::handle_write(const boost::system::error_code& ec)
{
    if (stopped_)
        return;
    
    if (!ec)
    {
        // Wait 10 seconds before sending the next heartbeat.
        //heartbeat_timer_.expires_after(boost::asio::chrono::seconds(10));
        //heartbeat_timer_.async_wait(boost::bind(&AdvancedClient::start_write, this));
    }
    else
    {
        std::cout << "Error on sending message: " << ec.message() << "\n";

        stop();
    }
    
}

void AdvancedClient::check_deadline()
{
    if (stopped_)
        return;

    // Check whether the deadline has passed. We compare the deadline against
    // the current time since a new asynchronous operation may have moved the
    // deadline before this actor had a chance to run.
    if (deadline_.expiry() <= steady_timer::clock_type::now())
    {
        // The deadline has passed. The socket is closed so that any outstanding
        // asynchronous operations are cancelled.
        socket_.close();

        // There is no longer an active deadline. The expiry is set to the
        // maximum time point so that the actor takes no action until a new
        // deadline is set.
        deadline_.expires_at(steady_timer::time_point::max());
    }

    // Put the actor back to sleep.
    deadline_.async_wait(boost::bind(&AdvancedClient::check_deadline, this));
}
