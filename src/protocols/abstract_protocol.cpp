/*
Copyright (C) 2014 Declan Ireland <http://github.com/torndeco/extDB>

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


#include "abstract_protocol.h"


AbstractProtocol::AbstractProtocol()
{
}

AbstractProtocol::~AbstractProtocol()
{
}

bool AbstractProtocol::callProtocol(std::string input_str, std::string &result, const int unique_id)
{
	// Returning False disables saveResult from extDB, used in VAC Protocol
	//  i.e return False when you are offloading work to another thread that will manage Result itself
	return true;
}

bool AbstractProtocol::init(AbstractExt *extension, const std::string &database_id, const std::string init_str)
{
	extension_ptr = extension;

	// Returning False indicates init Failed + Protocol Didn't load correctly
	return true;
}