/*
Copyright (C) 2015 Declan Ireland <http://github.com/torndeco/extDB>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/


#pragma once

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnection.h>
#include <Poco/Net/TCPServerConnectionFactory.h>

#include <Poco/Net/StreamSocket.h>

#include "protocols/abstract_ext.h"


class RemoteConnection: public Poco::Net::TCPServerConnection
	/// This class handles all client connections.
	///
	/// A string with the current date and time is sent back to the client.
{
public:
	RemoteConnection(const Poco::Net::StreamSocket& s, AbstractExt *extension):
		Poco::Net::TCPServerConnection(s),
		extension_ptr(extension)
	{
	}

	void run();
	bool login();
	
private:
	AbstractExt *extension_ptr;
};



class RemoteConnectionFactory: public Poco::Net::TCPServerConnectionFactory
	/// A factory for TimeServerConnection.
{
public:
	RemoteConnectionFactory(AbstractExt *extension):
		extension_ptr(extension)
	{
	}
	
	Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket)
	{
		return new RemoteConnection(socket, extension_ptr);
	}

private:
	AbstractExt *extension_ptr;
};


class RemoteServer
{
	public:
		void init(AbstractExt *extension);
		void stop();

	private:
		AbstractExt *extension_ptr;

		Poco::Net::TCPServerParams* pParams;
		Poco::Net::TCPServer *tcp_server;
};