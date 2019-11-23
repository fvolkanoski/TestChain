//
// sender.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "Network.h"

network::sender::sender(boost::asio::io_service& io_service, 
						const boost::asio::ip::address& multicast_address) : 
						endpoint_(multicast_address, multicast_port),
						socket_(io_service, endpoint_.protocol()),
						timer_(io_service),
						message_count_(0)
{
	std::ostringstream os;
	os << "Message " << message_count_++;
	message_ = os.str();

	socket_.async_send_to(
		boost::asio::buffer(message_), endpoint_,
		boost::bind(&sender::handle_send_to, this,
			boost::asio::placeholders::error));
}

void network::sender::handle_send_to(const boost::system::error_code& error)
{
	if (!error && message_count_ < max_message_count)
	{
		timer_.expires_from_now(boost::posix_time::seconds(1));
		timer_.async_wait(
			boost::bind(&sender::handle_timeout, this,
				boost::asio::placeholders::error));
	}
}

void network::sender::handle_timeout(const boost::system::error_code& error)
{
	if (!error)
	{
		std::ostringstream os;
		os << "Message " << message_count_++;
		message_ = os.str();

		socket_.async_send_to(
			boost::asio::buffer(message_), endpoint_,
			boost::bind(&sender::handle_send_to, this,
				boost::asio::placeholders::error));
	}
}
