//
// sender.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

namespace network
{
	const short multicast_port = 30001;
	const int max_message_count = 10;

	class sender
	{
	public:
		sender(boost::asio::io_service& io_service, const boost::asio::ip::address& multicast_address);

		void handle_send_to(const boost::system::error_code& error);
		void handle_timeout(const boost::system::error_code& error);

	private:
		boost::asio::ip::udp::endpoint endpoint_;
		boost::asio::ip::udp::socket socket_;
		boost::asio::deadline_timer timer_;
		int message_count_;
		std::string message_;
	};
}

#endif
