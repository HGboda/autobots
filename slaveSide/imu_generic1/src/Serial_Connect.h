/*
 * SerialConnect.h
 *
 *  Created on: Feb 14, 2015
 *      Author: srinivasan
 */

#ifndef SERIAL_CONNECT_H_
#define SERIAL_CONNECT_H_
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>

#include <iostream>

using boost::lexical_cast;
using boost::bad_lexical_cast;

class Serial_Connect {
public:
	Serial_Connect(std::string port, unsigned int baud_rate,unsigned long time_out);

	/*Default Constructor*/
	Serial_Connect();

	virtual ~Serial_Connect();

	/*not supported yet*/
	bool write(std::string s);

	/*readline*/
	std::string readLine_Until(const std::string &delim);

	bool handler(const boost::system::error_code& error,
				size_t bytes_transferred);

	void time_out(const boost::system::error_code& error);

//private:
	boost::asio::io_service io;
	boost::asio::serial_port serial;
	boost::asio::deadline_timer timer;
	unsigned long timeout = -1;
	bool read_error;
	volatile size_t totalBytes = 0;

};

#endif /* SERIAL_CONNECT_H_ */
