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


#pragma once

#include <Poco/AutoPtr.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/SessionPool.h>
#include <Poco/Util/IniFileConfiguration.h>

#include <boost/thread/thread.hpp>

#include "../spdlog/spdlog.h"


#define EXTDB_VERSION "40"
#define EXTDB_CONF_VERSION 1

class AbstractExt
{
	public:
		struct resultData
		{
			bool wait = true;
			std::string message;
		};

		// Database Connection Info
		struct DBConnectionInfo
		{
			std::string type;
			std::string connection_str;
			int min_sessions;
			int max_sessions;
			int idle_time;

			// Database Session Pool
			std::unique_ptr<Poco::Data::SessionPool> pool;
			boost::mutex mutex_pool;
		};

		// extDB Connectors
		struct extDBConnectors
		{
			bool mysql=false;
			bool sqlite=false;

			bool steam=false;
			bool rcon=false;
			bool remote=false;

			std::unordered_map<std::string, DBConnectionInfo> databases;
		};
		extDBConnectors extDB_connectors_info;

		// extDB Info
		struct extDBInfo
		{
			bool extDB_lock=false;
			int max_threads;

			std::string path;
			std::string log_path;
		};
		extDBInfo extDB_info;

		// RemoteAccess Info
		struct remoteAccessInfo
		{
			std::string password;
		};
		remoteAccessInfo remote_access_info;

		Poco::AutoPtr<Poco::Util::IniFileConfiguration> pConf;

		#ifdef TESTING
			std::shared_ptr<spdlog::logger> console;
		#endif

		std::shared_ptr<spdlog::logger> logger;
		std::shared_ptr<spdlog::logger> vacBans_logger;
	
		virtual void saveResult_mutexlock(const int &unique_id, const resultData &result_data)=0;

		virtual Poco::Data::Session getDBSession_mutexlock(DBConnectionInfo &database)=0;
		virtual Poco::Data::Session  getDBSession_mutexlock(DBConnectionInfo &database, Poco::Data::SessionPool::SessionDataPtr &session_data_ptr)=0;
		
		virtual void rconCommand(std::string str)=0;
		virtual void steamQuery(const int &unique_id, bool queryFriends, bool queryVacBans, std::vector<std::string> &steamIDs, bool wakeup)=0;
};